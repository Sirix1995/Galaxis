#ifndef GALAXISGRID_H
#define GALAXISGRID_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include "gridobject.h"

#define GRID_WIDTH 9
#define GRID_HEIGHT 7
#define SHIP_NUMBER 4

#define TEST_TIMER true

class GalaxisGrid : public QObject
{
    Q_OBJECT
public:
    ~GalaxisGrid();
    static void registerQml();
    static GalaxisGrid *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

public slots:
    Q_INVOKABLE void setRandomShips();
    Q_INVOKABLE void beaconCall(int x, int y);

signals:
    void callResult_shipsDetected(int x, int y, int numberOfDetections);
    void callResult_shipFound(int x, int y);

private slots:
    void randomCall();

private:
    explicit GalaxisGrid(QObject *parent = nullptr);
    static GalaxisGrid *m_pThis;

    QList<QList<GridObject *>> grid;

    QTimer* testTimer = nullptr;
};

#endif // Erreur dans «  Cpp.classToHeaderGuard(value('Class'), Util.suffix(value('HdrFileName'))) » : TypeError: Property 'classToHeaderGuard' of object CppEditor::Internal::CppToolsJsExtension(0x1fd3dc543b0) is not a function
