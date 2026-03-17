
#include <QDebug>
#include <QtQml/QQmlContext>
#include <QGuiApplication>

#include "qmlapp.h"

#include "viewpage/viewpage.h"
#include "viewpage/mainmenupage.h"
#include "viewpage/gamepage.h"
#include "galaxisgrid.h"

QmlApp::QmlApp(QWindow *parent)
    : QQuickView(parent)
{
    setResizeMode(QQuickView::SizeRootObjectToView);

    GalaxisGrid::registerQml();

    setWidth(1024);
    setHeight(768);

    loadMainMenu();
    show();
}

void QmlApp::viewChanger(ViewPage *page)
{
    if(!page) {
        qDebug() << "ERROR : null page sent to QmlApp.";
        return;
    }
    page->enableUiLink();
    if (m_page && page != m_page)
        m_page->deleteLater();
    m_page = page;
    page->show();
}

void QmlApp::loadMainMenu()
{
    ViewPage* mainMenuPage = new MainMenuPage(this);

    connect(mainMenuPage, SIGNAL(newSoloGame()), this, SLOT(loadGamePage()));
    connect(mainMenuPage, SIGNAL(quitApplication()), qApp, SLOT(quit()));

    viewChanger(mainMenuPage);
}

void QmlApp::loadGamePage()
{
    GalaxisGrid::instance()->gameStart();

    ViewPage* gamePage = new GamePage(this);

    connect(gamePage, SIGNAL(backToMainMenu()), this, SLOT(loadMainMenu()));

    viewChanger(gamePage);
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
