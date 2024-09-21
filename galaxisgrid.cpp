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

    int counter = 0;

    while(counter < SHIP_NUMBER) {
        int x = QRandomGenerator::global()->bounded(GRID_WIDTH - 1);
        int y = QRandomGenerator::global()->bounded(GRID_HEIGHT - 1);

        if(grid[x][y] && !isShip(x, y)) {
            grid[x][y]->setType(GridObject::GRIDOBJECT_SHIP);
            counter++;
        }

        QDBG_GREEN() << "Ship " << counter << " placed at " << x << " - " << y << "." << DBG_CLR_RESET;
    }
}

int GalaxisGrid::beaconCall(int x, int y)
{
    QDBG_YELLOW() << "Radar call at " << x << " - " << y << " !" << DBG_CLR_RESET;

    GridObject* currentGridObject = grid[x][y];
    if(!currentGridObject) {
        QDBG_RED() << "ERROR ! Null grid object at " << x << " - " << y << "." << DBG_CLR_RESET;
        return -1;
    }

    if(currentGridObject->type() == GridObject::GRIDOBJECT_SHIP) {
        QDBG_GREEN() << "Ship found at " << x << " - " << y << " !" << DBG_CLR_RESET;
        emit callResult_shipFound(x, y);
        return 5;
    }

    currentGridObject->setBeaconCounter(0);
    int shipCount = 0;
    int radarX = x;
    int radarY = y;
    bool shipFound = false;

    //left
    while(radarX >= 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX--;
    }

#if VERBOSE
    qDebug() << "After left : " << shipCount;
#endif

    radarX = x;
    shipFound = false;

    //Right
    while(radarX < GRID_WIDTH && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX++;
    }

#if VERBOSE
    qDebug() << "After right : " << shipCount;
#endif

    radarX = x;
    shipFound = false;

    //Under
    while(radarY >= 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarY--;
    }

#if VERBOSE
    qDebug() << "After under : " << shipCount;
#endif

    radarY = y;
    shipFound = false;

    //Above
    while(radarY < GRID_HEIGHT && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarY++;
    }

#if VERBOSE
    qDebug() << "After above : " << shipCount;
#endif

    radarY = y;
    shipFound = false;

    //Diago left above
    while(radarX >= 0 && radarY >= 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX--;
        radarY--;
    }

#if VERBOSE
    qDebug() << "After left above : " << shipCount;
#endif

    radarX = x;
    radarY = y;
    shipFound = false;

    //Diago right above
    while(radarX < GRID_WIDTH && radarY >= 0 && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX++;
        radarY--;
    }

#if VERBOSE
    qDebug() << "After right above : " << shipCount;
#endif

    radarX = x;
    radarY = y;
    shipFound = false;

    //Diago left under
    while(radarX >= 0 && radarY < GRID_HEIGHT && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX--;
        radarY++;
    }

#if VERBOSE
    qDebug() << "After left under : " << shipCount;
#endif

    radarX = x;
    radarY = y;
    shipFound = false;

    //Diago right under
    while(radarX < GRID_WIDTH && radarY < GRID_HEIGHT && !shipFound) {
        GridObject* scannedObject = grid[radarX][radarY];

        if(!scannedObject) {
            QDBG_RED() << "ERROR ! Null grid object at " << radarX << " - " << radarY << "." << DBG_CLR_RESET;
            return -1;
        }

        if(scannedObject->type() == GridObject::GRIDOBJECT_SHIP) {
            shipFound = true;
            shipCount++;
        }

        radarX++;
        radarY++;
    }

#if VERBOSE
    qDebug() << "After right under : " << shipCount;
#endif

    QDBG_YELLOW() << "Call result : " << shipCount << " ships detected.";
    currentGridObject->setBeaconCounter(shipCount);
    emit callResult_shipsDetected(x, y, shipCount);
    return shipCount;
}

int GalaxisGrid::getGridWidth()
{
    return GRID_WIDTH;
}

int GalaxisGrid::getGridHeight()
{
    return GRID_HEIGHT;
}

bool GalaxisGrid::isShip(int x, int y)
{
    //qDebug() << x << " - " << y;
    return (grid[x][y]->type() == GridObject::GRIDOBJECT_SHIP);
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
