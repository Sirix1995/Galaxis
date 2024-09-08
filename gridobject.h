#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H

#include <QObject>

class GridObject : public QObject
{
    enum gridObjectType_e {
        GRIDOBJECT_BEACON,
        GRIDOBJECT_SHIP,
        GRIDOBJECT_VOID
    };

    Q_OBJECT
    public:
        explicit GridObject(QObject *parent = nullptr);

    private:
        gridObjectType_e m_type;
        int m_beaconCounter;
        bool shipDiscovered;

    signals:
};

#endif // GRIDOBJECT_H
