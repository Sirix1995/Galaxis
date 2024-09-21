import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    id: root

    property int gridX: 0
    property int gridY: 0

    property int beaconNumber: 6

    color: baseColor

    property color baseColor: "skyblue"
    property color nothingColor: "lightgrey"

    signal objectClicked()

    width: 50
    height: width
    radius: height

    Label {
        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pointSize: 24

        text: beaconNumber

        visible: (beaconNumber < 5)
    }

    MouseArea {
        id: selectMa

        acceptedButtons: Qt.LeftButton

        anchors.fill: parent

        onClicked: objectClicked()
    }

    MouseArea {
        id: nothingMa

        acceptedButtons: Qt.RightButton

        anchors.fill: parent

        onClicked: {
            var set = false
            if(root.color == baseColor) {
                root.color = nothingColor
                set = true
            }
            if(root.color == nothingColor && !set)
                root.color = baseColor
        }
    }
}
