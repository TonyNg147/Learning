#ifndef LOGGER_H
#define LOGGER_H

#include <list>
#include <vector>
#include "LogRecord.h"
#include "LogSink.h"
namespace LoggerUtils
{
    class Logger final
    {
        friend class LogRecord;
        friend class LogCore;

        public:
            
            Logger();

            ~Logger();

            LogRecord createRecord(int moduleId, std::string content, LogSeverity);

        private:

            void submit(const LogRecord& logRecord);

    };

    class LogCore final
    {
        struct ModuleLoggingInfo
        {
            ModuleLoggingInfo(uint32_t _moduleID, std::string _moduleName, LogSeverity _severity)
                :moduleID(_moduleID)
                ,moduleName{_moduleName}
                ,severity{_severity}
            {

            }
            
            uint32_t moduleID;

            std::string moduleName;

            LogSeverity severity;
        };

        private:
            LogCore() = default;


        public:

            static LogCore& getInstance();
            
            void setApplicationName(const std::string& app);

            uint32_t registerModule(std::string module, LogSeverity severity);

            void addSink(LoggingSink);

            void submitRecord(const LogRecord& record);

            

        private:

            std::vector<ModuleLoggingInfo>  modules;

            std::string applicationName;

            std::list<LogSink*> sinks;


    };
};
#endif //LOGGER_H