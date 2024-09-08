import QtQuick
import "."

AppRectangle {
    id:control
    radius: 9
    property bool hasBackButton: true

    width: parent.width*0.8
    height: parent.height*0.9
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    property alias footerPositionY: backButton.y
    property alias backButton: backButton

    signal back()

    function show(){ control.visible = true }
    function hide(){ control.visible = false }

    AppButton {
        id: backButton
        x: 50
        y: 452
        text: "Retour"
        visible: control.hasBackButton
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 8
        onClicked: { control.back() ; control.visible = false}
    }
}
