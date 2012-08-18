import QtQuick 1.1
import com.nokia.symbian 1.1
import com.wadobo.remotecontrolplugin 1.0

PageStackWindow {
    id: window
    initialPage: Qt.createComponent("TouchpadPage.qml")
    showStatusBar: true
    showToolBar: true

    NetworkManager {
        id: networkManager
    }

    CommandManager {
        id: commandManager
        networkManager: networkManager
    }

    /*
    ToolBar {
        id: bottomToolbar
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
    }
    */

    Menu {
        id: mainMenu
        // define the items in the menu and corresponding actions
        content: MenuLayout {
            MenuItem {
                text: "Touchpad"
                onClicked: window.pageStack.replace(Qt.resolvedUrl("TouchpadPage.qml"))
            }
            MenuItem {
                text: "Keyboard"
                onClicked: window.pageStack.replace(Qt.resolvedUrl("KeyboardPage.qml"))
            }
            MenuItem {
                text: "Settings"
                onClicked: window.pageStack.push(Qt.resolvedUrl("ConnectionPage.qml"))
            }
        }
    }
}

