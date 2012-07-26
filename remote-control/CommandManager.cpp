#include "CommandManager.h"

#include <QNetworkAccessManager>
#include <QDebug>

CommandManager::CommandManager(QObject *parent) :
    QObject(parent), mConnected(false)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mCommandString.insert(KeyCommand, "key");
    mCommandString.insert(KeyDownCommand, "keydown");
    mCommandString.insert(KeyUpCommand, "keyup");
    mCommandString.insert(StringCommand, "str");
    mCommandString.insert(MouseClickCommand, "mouseclick");
    mCommandString.insert(MouseMoveCommand, "mousemove");
    mCommandString.insert(MouseRelativeMoveCommand, "mousermove");
    mCommandString.insert(MouseDownCommand, "mousedown");
    mCommandString.insert(MouseUpCommand, "mouseup");
    mCommandString.insert(SleepCommand, "sleep");
    mCommandString.insert(MicroSleepCommand, "usleep");
}


void CommandManager::runCommand(CommandManager::InputCommand commandType,
                                QString args)
{
    if (commandType < 0 || commandType >= LastCommand) {
        qDebug() << "Command no implemented: " << commandType;
    }
    QString commandLine = mCommandString.value(commandType) + " " + args;
    qDebug() << "runCommand" << commandType << commandLine;
}
