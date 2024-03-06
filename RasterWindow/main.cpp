#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "raster.h"
#include <WindowCustom.h>
#include <QQmlComponent>
int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("SIDS_UIApp"));
    QQmlEngine engine;
    qWarning()<<"Gui thread is "<<QThread::currentThreadId();
    engine.addImportPath(":/");
    qmlRegisterType<WindowCustom>("WindowCustom",1,0,"WindowCustom");
    QQmlComponent component(&engine, QUrl("qrc:/HMI/main.qml"));
    qWarning()<<"Error when create component is " << component.errors();
    QWindow* window = qobject_cast<QWindow*>(component.create());
    if (window)
    {
        window->show();
    }
    return app.exec();
};