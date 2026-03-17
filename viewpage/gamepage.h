#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QObject>
#include <viewpage/viewpage.h>

class GamePage : public ViewPage
{
    Q_OBJECT
public:
    GamePage(QObject *parent,
             QString uiFilePath = "qrc:/qml/GamePage.qml",
             QString metaLinkRef = "gamePageUiLink");
    ~GamePage();

public slots:

signals:
    void backToMainMenu();

private slots:

private:
};

#endif // GAMEPAGE_H
