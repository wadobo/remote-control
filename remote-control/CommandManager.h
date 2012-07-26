#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QMap>
#include <QAbstractSocket>
#include <QStringList>
#include <QNetworkAddressEntry>

class QNetworkAccessManager;
class QTcpSocket;
class QNetworkProxy;
class QAuthenticator;
class QVariant;

class CommandManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(InputCommand)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)

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

    enum State {
        UnconnectedState,
        ConnectedState,
        ConnectingState,
        AutoConnectingState
    };
    explicit CommandManager(QObject *parent = 0);

    QString state() const { return ""; }
signals:
    void connectedChange(bool);
    void stateChanged(QString);

public slots:
    void automaticConnection();
    void runCommand(const InputCommand command, const QVariant &args);
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

    // Variables
    QMap<InputCommand, QString> mCommandString;
    /**
      * Possible states are: Unconnected, connected, connecting, automaticConnecting
      */
    State mState;
    QTcpSocket *mSocket;
    QList<QNetworkAddressEntry> mAutoConnectionAddressList;
    QNetworkAddressEntry mActualAddress;

    short mPort;
};

#endif // COMMANDMANAGER_H
