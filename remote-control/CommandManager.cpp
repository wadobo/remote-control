#include "CommandManager.h"

#include <QNetworkAccessManager>
#include <QTcpSocket>


#include <QDebug>


CommandManager::CommandManager(QObject *parent) :
    QObject(parent)
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

    // Creating socket
    mSocket = new QTcpSocket(this);
    connect(mSocket, SIGNAL(connected()), this, SLOT(connectedSlot()));
    connect(mSocket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    connect(mSocket, SIGNAL(hostFound()), this, SLOT(hostFoundSlot()));
    connect(mSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(mSocket,
            SIGNAL(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)),
            this,
            SLOT(proxyAuthenticationRequiredSlot(const QNetworkProxy&, QAuthenticator*)));
    connect(mSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,
            SLOT(stateChangedSlot(QAbstractSocket::SocketState)));

    mSocket->connectToHost("127.0.0.1", 8888);
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

void CommandManager::connectedSlot()
{
    qDebug() << "socket: connected";
    mSocket->write("holaaaaaaaaaaaaa");
}

void CommandManager::disconnectedSlot()
{
    qDebug() << "socket: disconnected";
}

void CommandManager::hostFoundSlot()
{
    qDebug() << "socket: hostFoundSlot";
}

void CommandManager::errorSlot(QAbstractSocket::SocketError error)
{
    qDebug() << "socket: error " << error;
}

void CommandManager::proxyAuthenticationRequiredSlot(const QNetworkProxy &, QAuthenticator *)
{
    qDebug() << "socket: proxyAuthenticationRequired";
}

void CommandManager::stateChangedSlot(QAbstractSocket::SocketState state)
{
    qDebug() << "socket: state changed" << state;
}
