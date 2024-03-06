#include <Logger.h>
#include <mutex>
#include "ConsoleSink.h"
namespace LoggerUtils
{
    static LogCore* g_singletonLogCore = nullptr;

    LogRecord::LogRecord(Logger& _logger, int _moduleId, std::string _content, LogSeverity _severity)
        :logger{_logger}
        ,moduleId{_moduleId}
        ,content{_content}
        ,severity{_severity}
        ,timeStamp{std::time(nullptr)}
    {
        
    }

    LogRecord::LogRecord(const LogRecord& other)
        :logger{other.logger}
        ,moduleId{other.moduleId}
        ,content{other.content.str()}
        ,severity{other.severity}
        ,timeStamp{other.timeStamp}
    {

    }

    LogRecord& LogRecord::operator<< (const char* str)
    {
        content << str;
        return *this;
    }

    LogRecord::~LogRecord()
    {
        logger.submit(*this);
    }

    Logger::Logger()
    {

    }

    Logger::~Logger()
    {

    }

    LogRecord Logger::createRecord(int moduleId, std::string content, LogSeverity severity)
    {
        return LogRecord(*this, moduleId, content, severity);
    }

    void Logger::submit(const LogRecord& logRecord)
    {
        if (g_singletonLogCore != nullptr)
        {
            g_singletonLogCore->submitRecord(logRecord);
        }
    }

    LogCore& LogCore::getInstance()
    {
        static std::once_flag flag;
        std::call_once(flag,[=]() -> void
        {
            g_singletonLogCore = new LogCore();
        });

        return *g_singletonLogCore;
    }

    void LogCore::setApplicationName(const std::string& app)
    {
        applicationName = app;
    }

    uint32_t LogCore::registerModule(std::string moduleName, LogSeverity severity)
    {
        for (auto& module: modules)
        {
            if (module.moduleName == moduleName)
            {
                return UINT32_MAX;
            }
        }

        uint32_t currentID = modules.size();

        modules.emplace_back(currentID, moduleName, severity);

        return currentID;
    }

    void LogCore::addSink(LoggingSink sinkType)
    {
        LogSink* sink = nullptr;

        switch(sinkType)
        {
            case LoggingSink::Console:
            {
                sink = new ConsoleSink();
                break;
            }
            default:
            {
                break;
            }
        }

        if (sink != nullptr)
        {
            sinks.push_back(sink);
        }
    }

    void LogCore::submitRecord(const LogRecord& record)
    {
        uint32_t id = 0;
        std::string moduleName    = "";
        std::string severityLabel = "";

        for (; id < modules.size(); ++id)
        {
            if (record.moduleId == modules[id].moduleID) 
            {
                break;
            }
        }

        

        if (id == modules.size())
        {
            return;
        }

        static const char* s_severityLabel[5] = 
        {
            "Debug",
            "Info",
            "Warning",
            "Critical",
            "Fatal",
        };

        if (modules[id].severity > LogSeverity::Fatal || modules[id].severity < LogSeverity::Debug)
        {
            fprintf(stderr, "Invalid Severity. Please Choose the correct one !");
            return;
        }

        if (modules[id].severity > record.severity)
        {
            return;
        }
        
        moduleName = modules[id].moduleName;
        severityLabel = s_severityLabel[static_cast<int>(record.severity)];

        std::list<LogSink*>::iterator it = sinks.begin();
        while (it != sinks.end())
        {
            if (*it == nullptr)
            {
                sinks.erase(it++);
            }
            else
            {
                (*it)->submitRecord(applicationName, moduleName, severityLabel, record);
                ++it;
            }
        }

    }

};