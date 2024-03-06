#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <thread>
#define BT_BUFF_SIZE (100)

void getBacktrace()
{
    void* btAddress[4096];
    size_t btSize = backtrace(btAddress, 4096);
    if (btSize < 4096)
    {
        printf("Full program stacks are stored\n");
    };

    char** parseBt = backtrace_symbols(btAddress, btSize);
    if (parseBt == NULL)
    {
        perror("Cannot get the verbose backtrace\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i=0; i < btSize; ++i)
    {
        if (parseBt[i] != NULL)
        {
            printf("%s\n", parseBt[i]);
        } 
    }

    free(parseBt);

    std::abort();
}

static void coredump_handler(int signo, siginfo_t *info, void *context)
{
    do
    {
        if (signo != SIGSEGV)
        {
            break;
        }

        getBacktrace();
        printf("Herererer 1\n");

    }
    while(0);
    printf("Herererer 2\n");
    if ( SIG_DFL != nullptr)
    {
        (void)signal(signo, SIG_DFL);
    }
    (void)raise(signo);
}

void accessInvalidPointer(int*& p)
{
    int a = 5;
    p = &a;
    printf("In herer\n");
}
#include <chrono>

int main(int argc, char** arg)
{
    printf("Initialize program !!!\n");
    struct  sigaction _coreDumpAct = {0};
    _coreDumpAct.sa_flags  = SA_SIGINFO ;
    _coreDumpAct.sa_sigaction = &coredump_handler;
    if (sigaction(SIGSEGV, &_coreDumpAct, NULL) == -1)
    {
        perror("Cannot bind sigaction\n");
        exit(EXIT_FAILURE);
    }
    int *p;
    // while(1)
    // {
    //     int* p = new int();
    //     delete p;
    //     * p = 10;
    // }
    // accessInvalidPointer(p);
    // std::this_thread::sleep_for(std::chrono::seconds(5));
    printf("Wake up\n");
        (void)std::set_terminate([]()
    {
        printf("Call set terminate\n");
        std::abort();
    });
    *p = 6;



}