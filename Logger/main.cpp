#include <CoreDumpHandler.h>
#include <Logger.h>
int main(int argc, char** argv)
{
    (void)LoggerUtils::CoreDumpHandler::getInstance();

    // Dummy

    // int *p = nullptr;

    // *p = 5;

    // Dummy

    LoggerUtils::LogCore& logCore = LoggerUtils::LogCore::getInstance();

    logCore.setApplicationName("DemoApp");

    uint32_t moduleId = logCore.registerModule("Cpp", LoggerUtils::LogSeverity::Debug);

    logCore.addSink(LoggerUtils::LoggingSink::Console);


    LoggerUtils::Logger log;

    log.createRecord(moduleId, "Nguyen vip pro", LoggerUtils::LogSeverity::Info);





}