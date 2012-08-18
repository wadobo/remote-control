import QtQuick 1.1
import com.nokia.symbian 1.1
import com.wadobo.remotecontrolplugin 1.0

PageStackWindow {
    id: window
    //initialPage: touchpadPage
    initialPage: connectionPage
    showStatusBar: true
    showToolBar: true

    NetworkManager {
        id: networkManager
    }

    CommandManager {
        id: commandManager
        networkManager: networkManager
    }

    ToolBar {
        id: bottomToolbar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            ButtonRow {
                TabButton {
                    id: tabButton1
                    text: "Mouse"
                    onClicked: pageStack.push(touchpadPage)
                }
                TabButton {
                    id: tabButton2
                    text: "Keyboard"
                    onClicked: pageStack.push(keyboardPage)

                }
                TabButton {
                    iconSource: "toolbar-menu"
                    onClicked: Qt.quit()
                }
            }
        }
    }

   TouchpadPage {
       id: touchpadPage
       tools: bottomToolbar
   }

   KeyboardPage {
       id: keyboardPage
       tools: bottomToolbar
   }

   ConnectionPage {
       id: connectionPage
       tools: bottomToolbar
   }
}

