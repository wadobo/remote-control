#include <QApplication>
#include "qmlapplicationviewer.h"
#include "CommandManager.h"

#include <QNetworkAccessManager>
#include <QDeclarativeContext>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QNetworkAccessManager networkManager;
    CommandManager commandManager(&networkManager);
    QmlApplicationViewer viewer;
    QDeclarativeContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("commandManager", &commandManager);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/remotecontrol/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
