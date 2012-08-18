// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    /* Autoconnection is Not implemented yet
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
    */

    property int defaultMargin: 10 // plataformStyle.paddingSmall

    tools: SettingsToolBar {}

    Label {
        id: hostLabel
        anchors {
            top: parent.top
            left: parent.left
            margins: defaultMargin
        }
        text: "Host:"
    }

    TextField {
        id: hostField
        anchors {
            top: hostLabel.bottom
            left: parent.left
            right: parent.right
            margins: defaultMargin
        }
        placeholderText: "192.168.1.2"
        text: "192.168.1.2"
    }

    Label {
        id: portLabel
        anchors {
            top: hostField.bottom
            left: parent.left
            margins: defaultMargin
        }
        text: "Port:"
    }

    TextField {
        id: portField
        anchors {
            top: portLabel.bottom
            left: parent.left
            right: parent.right
            margins: defaultMargin
        }
        placeholderText: "8888"
        text: "8888"
    }

    Button {
        id: manualConnectButton
        text: "Connect"
        anchors {
            top: portField.bottom
            horizontalCenter: parent.horizontalCenter
            margins: defaultMargin
        }
        onClicked: {
            networkManager.connectToHost(hostField.text, parseInt(portField.text))
        }
        enabled: portField.text && hostField.text
    }
}
