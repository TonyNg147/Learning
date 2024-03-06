#include <CoreDumpHandler.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <dlfcn.h>
#include <cstddef>
#include <sstream>
#include <wait.h>
#include <iomanip>
#include <exception>
#include <string.h>
#include <mutex>
namespace LoggerUtils
{
    static CoreDumpHandler* g_singleton = nullptr;

    CoreDumpHandler* CoreDumpHandler::getInstance()
    {
        static std::once_flag flag;
        std::call_once(flag, [=]() -> void
        {
            g_singleton = new CoreDumpHandler();
        });
        return g_singleton;
    }

    static constexpr int STACK_FRAME = 256; 

    std::string CoreDumpHandler::getBackTrace()
    {
        void* bt[STACK_FRAME];
        
        size_t btRet = backtrace(bt, STACK_FRAME);

        std::stringstream content;

        std::stringstream offsetStream;

        std::stringstream temp;

        if (btRet <= STACK_FRAME)
        {
            printf("Backtrace is stored full\n");
        }
        else
        {
            printf("Backtrace may not be stored entirely\n");
        }

        int j = 1;

        for (size_t i = 0 ; i < btRet; ++i)
        {
            Dl_info info;

            if (dladdr(bt[i], &info) == 0)
            {
                continue;
            }

            temp.width(4);

            temp << std::right << j++ << ". ";

            std::ptrdiff_t offset = static_cast<char*>(bt[i]) - static_cast<char*>(info.dli_fbase);

            offsetStream << std::hex <<  offset;

            do
            {
                int pipeFd[2];

                if (pipe(pipeFd) == -1)
                {
                    fprintf(stderr, "Cannot Make a pipe. Error is %s\n", strerror(errno));
                    break;
                }

                pid_t childPID = fork();

                if (childPID < 0)
                {
                    close(pipeFd[0]);
                    close(pipeFd[1]);
                    break;
                }

                if (childPID == 0)
                {
                    close(pipeFd[0]);

                    do
                    {
                        if (dup2(pipeFd[1], STDOUT_FILENO) == -1)
                        {
                            fprintf(stderr, "Duplicate catches an error %s\n", strerror(errno));
                            close(pipeFd[1]);
                            break;
                        }

                        ssize_t execRet = execlp("/usr/bin/addr2line", "/usr/bin/addr2line", offsetStream.str().c_str(), "-s", "-p", "-C", "-f", "-e", info.dli_fname,NULL);

                        if (execRet == -1)
                        {
                            fprintf(stderr, "Execute Addr2line catches an error %s\n", strerror(errno));
                            close(pipeFd[1]);
                            break;
                        }

                       exit(EXIT_SUCCESS); 
                    } 
                    while (false);

                    exit(EXIT_FAILURE);
                }
                else
                {
                    close(pipeFd[1]);

                    int childExecutionStatus = -1;

                    waitpid(childPID, &childExecutionStatus, 0);

                    if (childExecutionStatus != 0)
                    {
                        break;
                    }

                    char buffer[4096];

                    ssize_t nBytes = read(pipeFd[0], buffer, 4096);

                    if (nBytes <= 0)
                    {
                        fprintf(stderr, "An error occured while reading from pipe. The error is %s\n", strerror(errno));
                        break;
                    }

                    if (nBytes >= 4096)
                    {
                        buffer[4096-1] = '\0';
                    }
                    else
                    {
                        buffer[nBytes] = '\0';
                    }

                    temp << buffer;

                    content << temp.str();

                }
            }
            while(false);

            offsetStream.str("");

            temp.str("");
        }

        return content.str();
    }

    void CoreDumpHandler::onSegmentFault(int sig, siginfo_t *info, void *ucontext)
    {
        if (sig != SIGSEGV)
        {
            return;
        }

        // Temporarily log out the content

        if (g_singleton)
        {
            printf("%s\n", g_singleton->getBackTrace().c_str());
        }

        

        (void)signal(sig,SIG_DFL);

        (void)raise(sig);
   
    }

    CoreDumpHandler::CoreDumpHandler()
    {
        struct sigaction _handler = {};
        _handler.sa_sigaction = &CoreDumpHandler::onSegmentFault;

        if (sigaction(SIGSEGV, &_handler, nullptr) == -1)
        {
            fprintf(stderr, "Cannot bind the handle for segment fault. The error is %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        std::set_terminate(&CoreDumpHandler::unHandleException);


    }

    void CoreDumpHandler::unHandleException()
    {
        std::exception_ptr ex = std::current_exception();
        try
        {
            std::rethrow_exception(ex);
        }
        catch(const std::exception& e)
        {
            fprintf(stderr, "Exception is %s\n", e.what());
            if (g_singleton)
            {
                printf("%s\n", g_singleton->getBackTrace().c_str());
            }
        }

        std::abort();
    }
};