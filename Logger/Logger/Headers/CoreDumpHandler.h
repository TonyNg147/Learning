#ifndef CORE_DUMP_HANLDER_H
#define CORE_DUMP_HANLDER_H
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string>
namespace LoggerUtils
{
    class CoreDumpHandler final
    {
        private:
        
            CoreDumpHandler();

        public:

            static CoreDumpHandler* getInstance();

        private:
            
            static void onSegmentFault(int, siginfo_t *, void *);

            static void unHandleException();

            std::string getBackTrace();

            
    };
};

#endif //CORE_DUMP_HANLDER_H