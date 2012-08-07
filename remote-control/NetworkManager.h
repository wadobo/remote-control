#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QAbstractSocket>
#include <QNetworkAddressEntry>

class QNetworkAccessManager;
class QTcpSocket;
class QNetworkProxy;
class QAuthenticator;
class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
public:
    // Different possible states
    enum State {
        UnconnectedState,
        ConnectedState,
        ConnectingState,
        AutoConnectingState // still unused
    };

    explicit NetworkManager(QObject *parent = 0);

    QString state() const { return ""; }
    bool sendToServer(const QString& string);
signals:
    void connectedChange(bool);
    void stateChanged(QString);


public slots:
    void automaticConnection();
    void connectedSlot();
    void disconnectedSlot();
    void hostFoundSlot();
    void errorSlot(QAbstractSocket::SocketError error);
    void proxyAuthenticationRequiredSlot(const QNetworkProxy& , QAuthenticator*);
    void stateChangedSlot(QAbstractSocket::SocketState state);

protected:
    // Functions
    void startAutomaticConnection();
    void nextAutomaticConnection();

    State mState;

    QTcpSocket *mSocket;
    QNetworkAddressEntry mActualAddress;
    QList<QNetworkAddressEntry> mAutoConnectionAddressList;

    short mPort;
};

#endif // NETWORKMANAGER_H
