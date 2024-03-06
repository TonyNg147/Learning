#include "ConsoleSink.h"
namespace LoggerUtils
{
    ConsoleSink::ConsoleSink()
    {

    }
    
    void ConsoleSink::submitRecord(const std::string& application, const std::string& module, const std::string& severityLabel, const LogRecord& record)
    {
        struct tm currentTimeFormat = *std::localtime(&record.timeStamp);
        static const char* format = 
        "[%s][%s][%s][%d/%d/%d-%d:%d:%d] %s";

        char buffer[4096];

        sprintf(buffer, format, application.c_str()
                              , module.c_str()
                              , severityLabel.c_str()
                              , currentTimeFormat.tm_mday
                              , currentTimeFormat.tm_mon + 1
                              , currentTimeFormat.tm_year + 1900
                              , currentTimeFormat.tm_hour 
                              , currentTimeFormat.tm_min 
                              , currentTimeFormat.tm_sec
                              , record.content.str().c_str()
        );

        printf("%s\n", buffer);
    }
};