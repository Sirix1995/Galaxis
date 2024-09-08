#include "viewpage.h"
#include <QQuickItem>
#include <QQuickView>

ViewPage::ViewPage(QObject *parent)
    : QObject(parent)
{
    parentView = ((QQuickView *) parent);
    context = parentView->rootContext();
}

ViewPage::ViewPage(QObject *parent, QString uiFilePath, QString metaLinkRef)
    : QObject(parent)
    , uiFile(uiFilePath)
    , metaLink(metaLinkRef)
{
    parentView = ((QQuickView *) parent);
    context = parentView->rootContext();
}

ViewPage::~ViewPage() {}

ViewPage *ViewPage::Create(QObject *parent, QString uiFilePath, QString metaLinkRef)
{
    return new ViewPage(parent, uiFilePath, metaLinkRef);
}

void ViewPage::loadView()
{
    parentView->setSource(QUrl(uiFile));
}

void ViewPage::show()
{
    QMetaObject::invokeMethod(this, "loadView", Qt::QueuedConnection);
}

QString ViewPage::getUiFilePath() const
{
    return uiFile;
}

void ViewPage::setUiFilePath(const QString &value)
{
    uiFile = value;
}

QString ViewPage::getMetaLink() const
{
    return metaLink;
}

void ViewPage::setMetaLink(const QString &value)
{
    metaLink = value;
}

void ViewPage::enableUiLink()
{
    context->setContextProperty(metaLink, this);
}

void ViewPage::setObjectLink(QString name, QObject *obj)
{
    context->setContextProperty(name, obj);
}

QList<QQuickItem *> ViewPage::getQmlItem(QString objName)
{
    return parentView->rootObject()->findChildren<QQuickItem *>(objName);
}

void ViewPage::setRootObjectProperty(const char *propertyName, const QVariant &value)
{
    parentView->rootObject()->setProperty(propertyName, value);
}

void ViewPage::setRootObjectProperty(QPair<const char *, const QVariant &> property)
{
    parentView->rootObject()->setProperty(property.first, property.second);
}

void ViewPage::setRootObjectProperty(QList<QPair<const char *, const QVariant &>> properties)
{
    while (properties.count()) {
        QPair<const char *, const QVariant &> prop = properties.takeFirst();
        setRootObjectProperty(prop);
    }
}

void ViewPage::setObjectProperty(const char *objName,
                                 const char *propertyName,
                                 const QVariant &value)
{
    QList<QQuickItem *> items = getQmlItem(objName);
    while (items.count()) {
        QQuickItem *item = items.takeFirst();
        item->setProperty(propertyName, value);
    }
}

void ViewPage::setObjectProperty(QQuickItem *item, const char *propertyName, const QVariant &value)
{
    item->setProperty(propertyName, value);
}

void ViewPage::setObjectProperty(const char *objName, QPair<const char *, const QVariant &> property)
{
    setObjectProperty(objName, property.first, property.second);
}

void ViewPage::setObjectProperty(const char *objName,
                                 QList<QPair<const char *, const QVariant &>> properties)
{
    while (properties.count()) {
        QPair<const char *, const QVariant &> prop = properties.takeFirst();
        setObjectProperty(objName, prop);
    }
}

void ViewPage::stringDBG(QString str)
{
    qDebug() << str;
}

void ViewPage::stringDBG(const QVariant &value)
{
    qDebug() << value;
}
