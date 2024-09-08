import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import "./style/"

AppRectangle {

    property int nbClick: 0
    property bool themeDark: true
    onThemeDarkChanged: {
        AppStyle.darkEnable = themeDark
    }

    ColumnLayout {
        id: column
        anchors.fill: parent

        AppLabel {
            id: label
            text: qsTr("===  " + nbClick + "  ===")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        AppButton {
            id: button
            text: qsTr("Button")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                nbClick++
                themeDark = !themeDark
                uiLink.stringDBG("nb click :" + nbClick)
            }
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
