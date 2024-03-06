#include <QWindow>
#include <QQuickWindow>
#include <QDebug>
#include <QtQml/qqmlregistration.h>
#include <QThread>
#include <QMouseEvent>
class WindowCustom: public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
    public:
        WindowCustom(QQuickWindow* parent = nullptr);
    protected:
        bool event(QEvent *ev) override
        {
            if (ev == nullptr) return false;
            QEvent::Type type = ev->type();
            bool isValidPress = true;
            switch(type)
            {
                case QEvent::TouchUpdate:
                {
                    qWarning()<<"Touch Update";
                    isValidPress = false;
                    break;
                }
                default:
                {
                    break;
                }
            }
            if (isValidPress)
            {
                return QQuickWindow::event(ev); 
            }
            return false;
        }

        void sceneGraphInitialized();

    private:
        bool isPressedBefore = false;

        QMouseEvent* pressEventBefore = nullptr;
};