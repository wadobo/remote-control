#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QMap>
#include <QAbstractSocket>

class QNetworkAccessManager;
class QTcpSocket;
class QNetworkProxy;
class QAuthenticator;
class QVariant;

class CommandManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(InputCommand)

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

signals:
    void connectedChange(bool);

public slots:
    void runCommand(const InputCommand command, const QVariant &args);
    void connectedSlot();
    void disconnectedSlot();
    void hostFoundSlot();
    void errorSlot(QAbstractSocket::SocketError error);
    void proxyAuthenticationRequiredSlot(const QNetworkProxy& , QAuthenticator*);
    void stateChangedSlot(QAbstractSocket::SocketState state);

protected:
    QMap<InputCommand, QString> mCommandString;
    QTcpSocket *mSocket;
    QNetworkAccessManager *mNetworkManager;
};

#endif // COMMANDMANAGER_H
