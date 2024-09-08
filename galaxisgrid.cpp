#include "galaxisgrid.h"

#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QRandomGenerator>

#include "tools/debug_info.h"

GalaxisGrid *GalaxisGrid::m_pThis = nullptr;

GalaxisGrid::GalaxisGrid(QObject *parent)
    : QObject(parent)
{
    QDBG_BLUE() << "Building grid..." << DBG_CLR_RESET;
    for(int i = 0; i < GRID_WIDTH; i++) {
        grid.append(QList<GridObject*>());
        for(int j = 0; j < GRID_HEIGHT; j++) {
            grid[i].append(new GridObject());
        }
    }

    if(TEST_TIMER) {
        testTimer = new QTimer();
        testTimer->setInterval(2000);
        testTimer->setSingleShot(false);
        connect(testTimer, &QTimer::timeout, this, &GalaxisGrid::randomCall);
        testTimer->start();
    }
}

void GalaxisGrid::registerQml()
{
    qmlRegisterSingletonType<GalaxisGrid>("GalaxisGrid",
                                          1,
                                          0,
                                          "GalaxisGrid",
                                          &GalaxisGrid::qmlInstance);
}

GalaxisGrid *GalaxisGrid::instance()
{
    if (m_pThis == nullptr) // avoid creation of new instances
    {
        m_pThis = new GalaxisGrid;
    }
    return m_pThis;
}

QObject *GalaxisGrid::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    // C++ and QML instance they are the same instance
    return GalaxisGrid::instance();
}

void GalaxisGrid::setRandomShips()
{
    QDBG_GREEN() << "Placing " << SHIP_NUMBER << " ships." << DBG_CLR_RESET;

    for(int i = 0; i < SHIP_NUMBER; i++) {
        int x = QRandomGenerator::global()->bounded(GRID_WIDTH - 1);
        int y = QRandomGenerator::global()->bounded(GRID_HEIGHT - 1);

        if(grid[x][y])
            grid[x][y]->setType(GridObject::GRIDOBJECT_SHIP);
        else
            QDBG_RED() << "ERROR ! Null grid object at " << x << " - " << y << "." << DBG_CLR_RESET;

        QDBG_GREEN() << "Ship " << i << " placed at " << x << " - " << y << "." << DBG_CLR_RESET;
    }
}

void GalaxisGrid::beaconCall(int x, int y)
{
    QDBG_YELLOW() << "Radar call at " << x << " - " << y << " !" << DBG_CLR_RESET;

    GridObject* currentGridObject = grid[x][y];
    if(!currentGridObject) {
        QDBG_RED() << "ERROR ! Null grid object at " << x << " - " << y << "." << DBG_CLR_RESET;
        return;
    }

    if(currentGridObject->type() == GridObject::GRIDOBJECT_SHIP) {
        QDBG_GREEN() << "Ship found at " << x << " - " << y << " !" << DBG_CLR_RESET;
        emit callResult_shipFound(x, y);
        return;
    }

    currentGridObject->setBeaconCounter(0);
    int shipCount = 0;
    int radarX = x;
    int radarY = y;
    bool shipFound = false;

    //Under
    while(radarX > 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX--;
    }

    radarX = x;
    shipFound = false;

    //Above
    while(radarX < GRID_WIDTH && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX++;
    }

    radarX = x;
    shipFound = false;

    //Left
    while(radarY > 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarY--;
    }

    radarY = y;
    shipFound = false;

    //Right
    while(radarY < GRID_HEIGHT && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarY++;
    }

    radarY = y;
    shipFound = false;

    //Diago left above
    while(radarX > 0 && radarY > 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX--;
        radarY--;
    }

    radarX = x;
    radarY = y;
    shipFound = false;

    //Diago right above
    while(radarX < GRID_WIDTH && radarY > 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX++;
        radarY--;
    }

    radarX = x;
    radarY = y;
    shipFound = false;

    //Diago left under
    while(radarX > 0 && radarY < GRID_HEIGHT && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX--;
        radarY++;
    }

    radarX = x;
    radarY = y;
    shipFound = false;

    //Diago right under
    while(radarX < GRID_WIDTH && radarY < GRID_HEIGHT && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX++;
        radarY++;
    }

    QDBG_YELLOW() << "Call result : " << shipCount << " ships detected.";
    currentGridObject->setBeaconCounter(shipCount);
    emit callResult_shipsDetected(x, y, shipCount);
}

void GalaxisGrid::randomCall()
{
    int x = QRandomGenerator::global()->bounded(GRID_WIDTH - 1);
    int y = QRandomGenerator::global()->bounded(GRID_HEIGHT - 1);
    beaconCall(x, y);
}

GalaxisGrid::~GalaxisGrid()
{
    delete(testTimer);
    for(int i = 0; i < grid.count(); i++)
        for(int j = 0; j < grid[i].count(); j++)
            delete grid[i][j];
}
