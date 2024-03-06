#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <Location.h>
#include <Student.h>
// #include <QQmlDebuggingEnabler>
int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableMetaObject(StudentInfoEnumartion::staticMetaObject, "AcademyControlBlock", 1, 0, "Location", "Access to enums & flags only");

    qmlRegisterType<Student>("AcademyControlBlock", 1, 0 , "Student");

    qmlRegisterType<LocationPlus>("AcademyControlBlock", 1, 0 , "LocationPlus");

    engine.load(QUrl("qrc:/main.qml"));

    // QQmlDebuggingEnabler enabler;

    return app.exec();
};