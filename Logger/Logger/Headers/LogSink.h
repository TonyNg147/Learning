#ifndef LOG_SINK_BASE_H
#define LOG_SINK_BASE_H
#include "LogRecord.h"
namespace LoggerUtils
{
    enum class LoggingSink
    {
        Console = 0,
    };

    class LogSink
    {
        friend class LogCore;

        protected:
            
            LogSink() = default;

            LogSink(const LogSink&) = delete;

            LogSink& operator=(const LogSink&) = delete;

        public:
            
            virtual void submitRecord(const std::string& application, const std::string& module, const std::string& severityLabel, const LogRecord& record) = 0;
    };


};

#endif //LOG_SINK_BASE_H
