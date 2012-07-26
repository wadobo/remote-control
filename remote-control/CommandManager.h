#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QMap>

class QNetworkAccessManager;

class CommandManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(InputCommand)

public:
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChange)

    enum InputCommand {
        KeyCommand,
        KeyDownCommand,
        KeyUpCommand,
        StringCommand,
        MouseClickCommand,
        MouseMoveCommand,
        MouseRelativeMoveCommand,
        MouseDownCommand,
        MouseUpCommand,
        SleepCommand,
        MicroSleepCommand,
        LastCommand
    };

    explicit CommandManager(QObject *parent = 0);

signals:
    void connectedChange(bool);

public slots:
    bool connected() const { return mConnected; }
    void runCommand(InputCommand command, QString args);

protected:
    QMap<InputCommand, QString> mCommandString;
    QNetworkAccessManager *mNetworkManager;
    bool mConnected;
};

#endif // COMMANDMANAGER_H
