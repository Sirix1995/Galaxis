#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H

#include <QObject>

class GridObject : public QObject
{
    Q_OBJECT
    public:
        explicit GridObject(QObject *parent = nullptr);

        enum gridObjectType_e {
            GRIDOBJECT_BEACON,
            GRIDOBJECT_SHIP,
            GRIDOBJECT_VOID
        };

        Q_ENUM(gridObjectType_e)

        gridObjectType_e type() const;
        void setType(gridObjectType_e newType);

        int beaconCounter() const;
        void setBeaconCounter(int newBeaconCounter);

        bool getShipDiscovered() const;
        void setShipDiscovered(bool newShipDiscovered);

    private:
        gridObjectType_e m_type = GRIDOBJECT_VOID;
        int m_beaconCounter = 0;
        bool shipDiscovered = false;

    signals:
};

#endif // GRIDOBJECT_H
