#include "CommandManager.h"

#include <QVariant>

CommandManager::CommandManager(QObject *parent) :
    QObject(parent), mNetworkManager(0)
{
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

void CommandManager::runCommand(const CommandManager::InputCommand commandType,
                                const QVariant& arguments)
{
    Q_ASSERT(mNetworkManager);
    Q_ASSERT(commandType < 0);
    Q_ASSERT(commandType >= LastCommand);

    QString commandLine = mCommandString.value(commandType) + " ";
    switch (commandType) {
    case MouseRelativeMoveCommand:
    case MouseMoveCommand:
        commandLine.append(arguments.toStringList().join(" "));
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
        commandLine.append(arguments.toString());
        break;
    default:
        break;
    }
    commandLine.append('\n');
    mNetworkManager->sendToServer(commandLine);
}
