import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    id: mainPage

    Rectangle {
        id: touchpadRectangle
        anchors.fill: parent
        color: gray
        MouseArea {
            id: touchpadArea
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }
}
