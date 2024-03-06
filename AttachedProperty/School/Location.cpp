#include "Location.h"

LocationController& LocationController::getInstance()
{
    static LocationController instance;
    return instance;
}

LocationController::LocationController()
    :m_plusInfo{
        {Location::NY, 5},
        {Location::LA, 10},
    }
{
    qWarning()<<"Create Location Controller";
}

int LocationController::findPlus(Location location)
{
    std::unordered_map<Location, int>::const_iterator it = m_plusInfo.find(location);

    if (it != m_plusInfo.cend())
    {
        return it->second;
    }

    return -1;
}

void StudentInfoAttachType::setLocation(Location location)
{
    if (m_location == location) return;

    m_location = location;

    LocationController& controller = LocationController::getInstance();

    int plus = controller.findPlus(location);

    if (plus != -1)
    {
        parent()->setProperty("point", QVariant(plus));
    }

    emit locationChanged();
}