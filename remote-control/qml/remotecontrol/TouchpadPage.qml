import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    Image {
        anchors.fill: parent
        //width: 120; height: 120
        fillMode: Image.Tile
        source: "qrc:/bg.jpg"

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

        MouseArea {
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
                        //xte.send(server, port, "mousermove " + xpos + " " + ypos);

                        prevX = mouseX;
                        prevY = mouseY;
                    }
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
