#include "WindowCustom.h"
#include <QThread>
WindowCustom::WindowCustom(QQuickWindow* parent)
    :QQuickWindow(parent)
{
    QObject::connect(this,&QQuickWindow::sceneGraphInitialized,this,&WindowCustom::sceneGraphInitialized, Qt::DirectConnection);
}

void WindowCustom::sceneGraphInitialized()
{
    qWarning()<<"Rendering Thread is "<<QThread::currentThreadId();
}

