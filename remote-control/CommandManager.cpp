#include "CommandManager.h"

#include <QNetworkAccessManager>
#include <QTcpSocket>
#include <QVariant>
#include <QStringList>
#include <QNetworkInterface>


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

//    mSocket->connectToHost("127.0.0.1", 8888);
}

void CommandManager::automaticConnection()
{
    foreach (const QNetworkInterface& interface, QNetworkInterface::allInterfaces()) {
        QNetworkInterface::InterfaceFlags flags = interface.flags();
        // Searching for local network interfaces
        if (interface.isValid() && (flags & QNetworkInterface::IsUp) &&
                (flags & QNetworkInterface::IsRunning) &&
                !(flags & QNetworkInterface::IsLoopBack)) {
            qDebug() << "Searching with interface: " << interface.humanReadableName();
            // For each address
            foreach (const QNetworkAddressEntry& entry, interface.addressEntries()) {
                qDebug() << entry.ip().toString();
            }
        }
    }
}

void CommandManager::runCommand(const CommandManager::InputCommand commandType,
                                const QVariant& args)
{
    if (commandType < 0 || commandType >= LastCommand) {
        qDebug() << "Command no implemented: " << commandType;
    }
    QString commandLine = mCommandString.value(commandType) + " ";
    switch (commandType) {
    case MouseRelativeMoveCommand:
    case MouseMoveCommand:
        commandLine.append(args.toStringList().join(" "));
        break;
    case KeyCommand:
    case KeyDownCommand:
    case KeyUpCommand:
    case MouseClickCommand:
    case MouseDownCommand:
    case MouseUpCommand:
    case StringCommand:
    case SleepCommand:
    case MicroSleepCommand:
        commandLine.append(args.toString());
        break;
    default:
        break;
    }
    commandLine.append('\n');
    mSocket->write(commandLine.toAscii());
    qDebug() << "sending command" << commandLine.trimmed();
}

void CommandManager::connectedSlot()
{
    qDebug() << "socket: connected";
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
