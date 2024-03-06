#ifndef CONSOLE_SINK_H
#define CONSOLE_SINK_H
#include <LogSink.h>
namespace LoggerUtils
{
    class ConsoleSink final: public LogSink
    {
        public:

            ConsoleSink();

            void submitRecord(const std::string& , const std::string& , const std::string& , const LogRecord&) override;
    };
};
#endif //CONSOLE_SINK_H