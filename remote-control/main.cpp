#include <QApplication>
#include "qmlapplicationviewer.h"
#include "CommandManager.h"

#include <QNetworkAccessManager>
#include <QDeclarativeContext>
#include <QtDeclarative>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    qmlRegisterType<CommandManager>("com.wadobo.remotecontrolplugin", 1, 0,
                                    "CommandManager");
    qmlRegisterType<NetworkManager>("com.wadobo.remotecontrolplugin", 1, 0,
                                    "NetworkManager");
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/remotecontrol/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
