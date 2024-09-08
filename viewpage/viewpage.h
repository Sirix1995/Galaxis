#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QObject>
#include <QQmlContext>
#include <QQuickView>
#include <QString>

class ViewPage : public QObject
{
    Q_OBJECT
public:
    explicit ViewPage(QObject *parent);
    ViewPage(QObject *parent,
             QString uiFilePath = "qrc:/qml/main.qml",
             QString metaLinkRef = "uiLink");

    ~ViewPage();

    static ViewPage *Create(QObject *parent,
                            QString uiFilePath = "qrc:/qml/main.qml",
                            QString metaLinkRef = "uiLink");

    void show();
    void enableUiLink();

    QString getUiFilePath() const;
    void setUiFilePath(const QString &value);

    QString getMetaLink() const;
    void setMetaLink(const QString &value);

    QList<QQuickItem *> getQmlItem(QString objName);

    void setRootObjectProperty(const char *propertyName, const QVariant &value);
    void setRootObjectProperty(QPair<const char *, const QVariant &> property);
    void setRootObjectProperty(QList<QPair<const char *, const QVariant &> > properties);

    void setObjectProperty(const char *objName, const char *propertyName, const QVariant &value);
    void setObjectProperty(QQuickItem *item, const char *propertyName, const QVariant &value);
    void setObjectProperty(const char *objName, QPair<const char *, const QVariant &> property);
    void setObjectProperty(const char *objName,
                           QList<QPair<const char *, const QVariant &> > properties);

    void setObjectLink(QString name, QObject *obj);

public slots:
    void stringDBG(QString str);
    void stringDBG(const QVariant &value);

private slots:
    void loadView();

signals:

private:
    QString uiFile = "qrc:/qml/main.qml";
    QString metaLink = "uiLink";
    QQmlContext *context = nullptr;
    QQuickView *parentView = nullptr;
};

#endif // VIEWPAGE_H
