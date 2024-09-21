
#include <QDebug>

#include <QtQml/QQmlContext>

#include "qmlapp.h"

#include "viewpage/viewpage.h"
#include "galaxisgrid.h"

QmlApp::QmlApp(QWindow *parent)
    : QQuickView(parent)
{
    setResizeMode(QQuickView::SizeRootObjectToView);
    m_page = new ViewPage(this, "qrc:/qml/main.qml", "uiLink");
    m_page->enableUiLink();

    GalaxisGrid::registerQml();
    GalaxisGrid::instance()->setRandomShips();

    setWidth(1024);
    setHeight(768);

    viewChanger(m_page);
    show();
}

void QmlApp::viewChanger(ViewPage *page)
{
    if (m_page && page != m_page)
        m_page->deleteLater();
    m_page = page;
    page->show();
}

/*
 * Gestion Close Event
 */
bool QmlApp::event(QEvent *event)
{
    if (event->type() == QEvent::Close) {
        // return true to cancel close event
    }
    return QQuickView::event(event);
}

QmlApp::~QmlApp() {}
