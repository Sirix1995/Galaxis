#ifndef GALAXISGRID_H
#define GALAXISGRID_H

#include <QObject>
#include <QQmlEngine>

class GalaxisGrid : public QObject
{
    Q_OBJECT
public:
    static void registerQml();
    static GalaxisGrid *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

public slots:

signals:

private slots:

private:
    explicit GalaxisGrid(QObject *parent = nullptr);
    static GalaxisGrid *m_pThis;
};

#endif // Erreur dans «  Cpp.classToHeaderGuard(value('Class'), Util.suffix(value('HdrFileName'))) » : TypeError: Property 'classToHeaderGuard' of object CppEditor::Internal::CppToolsJsExtension(0x1fd3dc543b0) is not a function
