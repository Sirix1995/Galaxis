#ifndef GALAXISGRID_H
#define GALAXISGRID_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include "gridobject.h"

#define GRID_WIDTH 9
#define GRID_HEIGHT 7
#define SHIP_NUMBER 4

#define SHIP_BEACON_VALUE 5

#define TEST_TIMER false
#define VERBOSE false

class GalaxisGrid : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged FINAL)

    public:
        ~GalaxisGrid();
        static void registerQml();
        static GalaxisGrid *instance();
        static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

        int score() const;
        void setScore(int newScore);

    public slots:
        Q_INVOKABLE void gameStart();
        Q_INVOKABLE void setRandomShips();
        Q_INVOKABLE int beaconCall(int x, int y);

        Q_INVOKABLE int getGridWidth();
        Q_INVOKABLE int getGridHeight();

        Q_INVOKABLE bool isShip(int x, int y);

    signals:
        void callResult_shipsDetected(int x, int y, int numberOfDetections);
        void callResult_shipFound(int x, int y);
        void victory();

        void scoreChanged();

    private slots:
        void randomCall();

    private:
        explicit GalaxisGrid(QObject *parent = nullptr);
        static GalaxisGrid *m_pThis;

        QList<QList<GridObject *>> grid;

        QTimer* testTimer = nullptr;
        int discoveredShips = 0;
        int m_score;
};

#endif // Erreur dans «  Cpp.classToHeaderGuard(value('Class'), Util.suffix(value('HdrFileName'))) » : TypeError: Property 'classToHeaderGuard' of object CppEditor::Internal::CppToolsJsExtension(0x1fd3dc543b0) is not a function
