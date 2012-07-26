// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    Rectangle {
        id: logo
        height: 150; width: 150
        anchors.horizontalCenter: parent.horizontalCenter
        color: "blue"
    }

    Button {
        id: autoConnectButton
        text: "Auto-Connect"
        anchors {
            top: logo.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        states: [
            State {
                name: "connecting"
                PropertyChanges {
                    target: autoConnectButton
                    text: "Connecting..."
                    enabled: false
                    // Call search and connect function
                }
            },
            State {
                name: "tryAgain"
                PropertyChanges {
                    target: autoConnectButton
                    text: "Try Again"
                    // Call search and connect function
                }
            }
        ]


        onClicked: {
            state = "connecting"
            //TODO on timeout show dialog
            dialog1.open()
        }
    }

    Button {
        id: manualSettings
        text: "Manual settings"
        anchors {
            top: autoConnectButton.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
        onClicked: {
            manualSettings.enabled = false
            ipLabel.visible = true
            ipAddress.visible = true
            portLabel.visible = true
            portNumber.visible = true
            manualConnectButton.visible = true
        }
    }


    Label {
        id: ipLabel
        anchors {
            top: manualSettings.bottom
            topMargin: 20
            left: parent.left
            leftMargin: 25
        }
        text: "Host:"
        visible: false
    }

    TextField {
        id: ipAddress
        anchors {
            verticalCenter: ipLabel.verticalCenter
            left: ipLabel.right
            leftMargin: 10
        }
        placeholderText: "192.168.1.2"
        visible: false
    }

    Label {
        id: portLabel
        anchors {
            top: ipLabel.bottom
            topMargin: 20
            left: parent.left
            leftMargin: 25
        }
        text: "Port:"
        visible: false
    }

    TextField {
        id: portNumber
        anchors {
            verticalCenter:  portLabel.verticalCenter
            left: portLabel.right
            leftMargin: 10
        }
        text: "8888"
        visible: false
    }

    Button {
        id: manualConnectButton
        text: "Connect"
        anchors {
            top: portNumber.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
        visible: false
    }
    QueryDialog {
        id: dialog1
        height: 230
        titleText: "Can not find computer"
        acceptButtonText: "Close"
        message: "Can not find a computer to connect, make sure that you are connected on the same network and that computer is running the server application"
    }

}
