import QtQuick
import QtQuick.Controls
import "."

ToolSeparator {
    id: control

    contentItem: Rectangle {
        implicitWidth: parent.vertical ? 1 : 24
        implicitHeight: parent.vertical ? 24 : 1
        color: AppStyle.globalPrimaryAccent
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
