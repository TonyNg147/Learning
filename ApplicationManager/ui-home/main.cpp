#ifndef APP_MAN_MAIN
#define APP_MAN_MAIN
#include <QtAppManCommon/global.h>
#include <QtAppManCommon/logging.h>
#include <QtAppManMain/main.h>
#include <QtAppManMain/configuration.h>
#include <QtAppManPackage/packageutilities.h>
#include <QtAppManManager/sudo.h>

using namespace QtAM;

int main(int argc, char** argv)
{
    Logging::initialize(argc,argv);
    try
    {
        Main a(argc, argv);
        Configuration cfg;
        cfg.parseWithArguments(QCoreApplication::arguments());
        a.setup(&cfg);
        a.loadQml(cfg.loadDummyData());
        a.showWindow(cfg.fullscreen() && !cfg.noFullscreen());
        return MainBase::exec();
    }
    catch(const std::exception& e)
    {
        qCritical(LogSystem) << "ERROR  "<<e.what();
        return 2; 
    }
};
#endif //APP_MAN_MAIN