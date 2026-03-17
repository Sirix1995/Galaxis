#ifndef MAINMENUPAGE_H
#define MAINMENUPAGE_H

#include <QObject>
#include <viewpage/viewpage.h>

class MainMenuPage : public ViewPage
{
    Q_OBJECT
public:
    MainMenuPage(QObject *parent,
                 QString uiFilePath = "qrc:/qml/MainMenuPage.qml",
                 QString metaLinkRef = "MainMenuUiLink");
    ~MainMenuPage();

public slots:

signals:
    void newSoloGame();
    void quitApplication();

private slots:

private:
};

#endif // MAINMENUPAGE_H
