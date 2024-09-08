#include "galaxisToolBox.h"

#include <QDebug>
#include <QTime>
#include <QCoreApplication>

void delay(int secs)
{
    qDebug("Delay...");
    QTime dieTime= QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
