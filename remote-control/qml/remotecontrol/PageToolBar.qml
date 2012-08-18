// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.symbian 1.1

// Toolbar for a normal page
ToolBarLayout {
    id: mainToolbar
    ToolButton {
        iconSource: "toolbar-back"
        onClicked: window.pageStack.depth <= 1 ? Qt.quit() : window.pageStack.pop()
    }
    ToolButton {
        iconSource: "toolbar-menu"
        onClicked: mainMenu.open()
    }
}
