#include "Student.h"




void Student::setName(const QString& name)
{
    if (m_name == name) return;

    m_name = name;

    emit nameChanged();
}

void Student::setAge(const int& age)
{
    if (m_age == age) return;

    m_age = age;

    emit ageChanged();
}

void Student::setPoint(const float& point)
{
    if (m_point == point) return;

    m_point = point;

    qWarning()<<"Set New point " << point;

    emit pointChanged();
}