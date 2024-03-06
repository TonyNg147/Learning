#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
#include <QDebug>
#include <QQmlEngine>
class Student: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(float point READ point WRITE setPoint NOTIFY pointChanged)
    QML_ELEMENT
    public:
        Student(QObject* parent = nullptr)
            :QObject{parent}
        {

        }

        ~Student()
        {

        }

        void setName(const QString&);

        void setAge(const int&);

        void setPoint(const float&);

        QString name() const
        {
            return m_name;
        }

        float point() const
        {
            return m_point;
        }

        int age() const
        {
            return m_age;
        }

    signals:

        void nameChanged();

        void ageChanged();

        void pointChanged();

    private:

        QString m_name = "";

        float m_point = 0.0f;

        int m_age     = 0;
        
};
#endif //STUDENT_H