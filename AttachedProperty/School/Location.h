#ifndef CLASS_H
#define CLASS_H
#include <QObject>
#include <QDebug>
#include <QQmlEngine>
namespace StudentInfoEnumartion
{
    Q_NAMESPACE
    enum class Type
    {
        NY = 0,
        LA = 1,
    };
    Q_ENUM_NS(Type);
};

typedef StudentInfoEnumartion::Type Location;

class LocationController
{
    private:
        LocationController();
        
    public:
        static LocationController& getInstance();

        int findPlus(Location);

    private:
        
        const std::unordered_map<Location, int> m_plusInfo;
};

class StudentInfoAttachType: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Location location READ location WRITE setLocation NOTIFY locationChanged)
    QML_ELEMENT
    QML_UNCREATABLE("This is attached type. Thus accessing it only through Student")
    public:
        StudentInfoAttachType(QObject* parent)
            :QObject{parent}
        {

        }

        ~StudentInfoAttachType()
        {

        }

        void setLocation(Location);

        Location location() const
        {
            return m_location;
        }

    signals:
        
        void locationChanged();

    private:
        
        Location m_location;
             
};

class LocationPlus: public QObject
{
    Q_OBJECT
    QML_ATTACHED(StudentInfoAttachType)
    QML_ELEMENT
    public:
        static StudentInfoAttachType *qmlAttachedProperties(QObject *object)
        {
            return new StudentInfoAttachType(object);
        }
};

#endif //CLASS_H