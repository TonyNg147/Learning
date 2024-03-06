#ifndef LOGRECORD_H
#define LOGRECORD_H
#include <sstream>
#include <ctime>
namespace LoggerUtils
{
    class Logger;
    class LogCore;

    enum class LogSeverity
    {
        Debug    = 0 ,
        Info     = 1 ,
        Warning  = 2 ,
        Critical = 3 ,
        Fatal    = 4 ,
    };

    class LogRecord final
    {
        friend class Logger;
        friend class LogCore;

        public:
            LogRecord& operator<< (const char* str);

            LogRecord(const LogRecord& other);

            ~LogRecord();

        protected:
            LogRecord(Logger& logger, int moduleId, std::string content, LogSeverity);

        private:

            Logger&    logger;

        public:

            int moduleId;

            std::stringstream content;

            LogSeverity severity;

            time_t     timeStamp;
 
    };
};

#endif //LOGRECORD_H