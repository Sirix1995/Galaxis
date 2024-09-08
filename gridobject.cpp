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

bool GridObject::getShipDiscovered() const
{
    return shipDiscovered;
}

void GridObject::setShipDiscovered(bool newShipDiscovered)
{
    shipDiscovered = newShipDiscovered;
}
