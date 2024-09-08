#include "galaxisgrid.h"

#include <QQmlApplicationEngine>
#include <QQmlEngine>

GalaxisGrid *GalaxisGrid::m_pThis = nullptr;

GalaxisGrid::GalaxisGrid(QObject *parent)
    : QObject(parent)
{}

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
