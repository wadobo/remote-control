import QtQuick 1.1
import com.nokia.symbian 1.1

PageStackWindow {
    id: window
    initialPage: MainPage {tools: toolBarLayout}
    showStatusBar: true
    showToolBar: true

   ToolBar {
        anchors.top: parent.top
        tools: ToolBarLayout {
            ButtonRow {
                TabButton {
                    id: tabButton1
                    tab: tab1
                    text: "Mouse"
                }
                TabButton {
                    id: tabButton2
                    tab: tab2
                    text: "Keyboard"
                }
                TabButton {
                    id: tabButton3
                    tab: tab3
                    text: "Media"
                }
                ToolButton {
                    iconSource: "toolbar-menu"
                }
            }
        }
    }
}

