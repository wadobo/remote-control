import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    Rectangle {
        id: touchpadRectangle
        anchors.fill: parent
        color: "grey"
        MouseArea {
            id: touchpadArea
            anchors.fill: parent
            hoverEnabled: true
            //onClicked: Qt.quit()

        }
        Text {
            id: coordinates
            anchors.top: parent.top
            anchors.right: parent.right
            text:"x: " + touchpadArea.mouseX +", y: " +touchpadArea.mouseY
        }
        Button {
            id: leftButton
            text: "Left button"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
        Button {
            id: rightButton
            text: "Right button"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
        }
    }
}
