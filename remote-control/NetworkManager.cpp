#include "NetworkManager.h"

#include <QNetworkAccessManager>
#include <QTcpSocket>
#include <QStringList>
#include <QNetworkInterface>

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent)
{
    mState = UnconnectedState;
    mPort = 8888;

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
}

bool NetworkManager::sendToServer(const QString &string)
{
    Q_ASSERT(mState == ConnectedState);
    qDebug() << "sending to server: " << string.trimmed();
    return mSocket->write(string.toAscii()) > 0;
}

void NetworkManager::automaticConnection()
{
    if (mState == AutoConnectingState) {
        return;
    }

    foreach (const QNetworkInterface& interface, QNetworkInterface::allInterfaces()) {
        QNetworkInterface::InterfaceFlags flags = interface.flags();
        // Searching for local network interfaces
        if (interface.isValid() && (flags & QNetworkInterface::IsUp) &&
                (flags & QNetworkInterface::IsRunning) &&
                !(flags & QNetworkInterface::IsLoopBack)) {
            qDebug() << "Searching on interface: " << interface.humanReadableName();
            mAutoConnectionAddressList = interface.addressEntries();
        }
    }

    mState = AutoConnectingState;
    startAutomaticConnection();
}

void NetworkManager::connectedSlot()
{
    qDebug() << "socket: connected";
}

void NetworkManager::disconnectedSlot()
{
    qDebug() << "socket: disconnected";
}

void NetworkManager::hostFoundSlot()
{
    qDebug() << "socket: hostFoundSlot";
}

void NetworkManager::errorSlot(QAbstractSocket::SocketError error)
{
    qDebug() << "socket: error " << error;
}

void NetworkManager::proxyAuthenticationRequiredSlot(const QNetworkProxy &, QAuthenticator *)
{
    qDebug() << "socket: proxyAuthenticationRequired";
}

void NetworkManager::stateChangedSlot(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::ConnectedState) {
        mState = ConnectedState;
        return;
    }
    if (mState == AutoConnectingState) {
        if (state == QAbstractSocket::UnconnectedState) {
            nextAutomaticConnection();
        }
    }
    qDebug() << "socket: state changed" << state;
}

void NetworkManager::startAutomaticConnection()
{
    if (mAutoConnectionAddressList.isEmpty()) {
        mState = UnconnectedState;
        mActualAddress = QNetworkAddressEntry();
        qDebug() << "Finishing unsuccessful autoconnecting";
    } else {
        mActualAddress = mAutoConnectionAddressList.takeFirst();
        QString address = mActualAddress.ip().toString();
        QStringList addressList = address.split(".");
        addressList.removeLast();
        addressList.append(QString::number(1));
        mActualAddress.setIp(QHostAddress(addressList.join(".")));
        mSocket->connectToHost(mActualAddress.ip(), mPort);
        qDebug() << "Starting searching in network" << mActualAddress.ip().toString();
    }
}

void NetworkManager::nextAutomaticConnection()
{
    QString address = mActualAddress.ip().toString();
    QStringList addressList = address.split(".");
    int dir = addressList.takeLast().toInt();
    if (dir == 254) {
        startAutomaticConnection();
        return;
    }
    dir++;
    addressList.append(QString::number(dir));
    mActualAddress.setIp(QHostAddress(addressList.join(".")));
    mSocket->connectToHost(mActualAddress.ip(), mPort);
    qDebug() << "Connecting IP: " << mActualAddress.ip().toString();
}
