#include "gridobject.h"

GridObject::GridObject(QObject *parent)
    : QObject{parent}
{

}

GridObject::gridObjectType_e GridObject::type() const
{
    return m_type;
}

void GridObject::setType(gridObjectType_e newType)
{
    m_type = newType;
}

int GridObject::beaconCounter() const
{
    return m_beaconCounter;
}

void GridObject::setBeaconCounter(int newBeaconCounter)
{
    m_beaconCounter = newBeaconCounter;
}

bool GridObject::getDiscovered() const
{
    return discovered;
}

void GridObject::setDiscovered(bool newDiscovered)
{
    discovered = newDiscovered;
}
