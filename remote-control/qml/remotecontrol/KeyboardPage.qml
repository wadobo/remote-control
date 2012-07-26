// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.symbian 1.1


Page {
    TextArea {
        id: textInput
        width: parent.width
    }

    Button {
        id: sendText
        text: "Send text"
        anchors {
            top: textInput.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

    }
}
