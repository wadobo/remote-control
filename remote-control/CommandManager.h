#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "NetworkManager.h"

#include <QObject>
#include <QMap>
#include <QAbstractSocket>
#include <QStringList>
#include <QNetworkAddressEntry>

class QVariant;

class CommandManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(InputCommand)
    Q_PROPERTY(NetworkManager* networkManager READ networkManager WRITE setNetworkManager)

public:
    /**
      * These are the possible commands to be send to the computer.
      * They are the same of xte Linux command. For more information
      * see "man xte".
      */
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

public slots:
    /**
      * Send the given command with the given arguments to the server
      */
    void runCommand(const InputCommand command, const QVariant &arguments);

    NetworkManager* networkManager() const { return mNetworkManager; }
    void setNetworkManager(NetworkManager* nm) { mNetworkManager = nm; }

protected:
    // Variables
    QMap<InputCommand, QString> mCommandString;
    NetworkManager *mNetworkManager;
};

#endif // COMMANDMANAGER_H
