import QtQuick 1.1
import com.nokia.symbian 1.1
import com.wadobo.commandplugin 1.0

Page {
    Rectangle {
        id: touchpadRectangle
        anchors.fill: parent
        color: "grey"

        MouseArea {
            id: touchpadArea
            anchors.fill: parent
            property int prevX: 0
            property int prevY: 0
            property int xpos: 0
            property int ypos: 0
            onPressed: {
                prevX = mouseX;
                prevY = mouseY;
            }

            onReleased: {
                prevX = 0;
                prevY = 0;
            }

            onPositionChanged: {
                xpos = mouseX - prevX;
                ypos = mouseY - prevY;

                console.log("drag (" + xpos + ", " + ypos + ")");
                commandManager.runCommand(CommandManager.MouseRelativeMoveCommand, [xpos, ypos]);
                //xte.send(server, port, "mousermove " + xpos + " " + ypos);

                prevX = mouseX;
                prevY = mouseY;
            }
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
            onClicked: {
                commandManager.runCommand(CommandManager.MouseClickCommand, Qt.LeftButton)
            }
        }
        Button {
            id: rightButton
            text: "Right button"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            onClicked: {
                commandManager.runCommand(CommandManager.MouseClickCommand, Qt.RightButton)
            }
        }
   }
}
