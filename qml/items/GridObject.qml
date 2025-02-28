import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    id: root

    enum GridObjectState {
        NOT_DISCOVERED,
        SHIP_DISCOVERED,
        RADAR_DISCOVERED,
        GREYED_OUT
    }

    property int gridX: 0
    property int gridY: 0

    property int beaconNumber: 6 //Not discovered value

    color: baseColor

    property color baseColor: "skyblue"
    property color nothingColor: "grey"
    property color radarColor: "khaki"
    property color shipColor: "salmon"

    property int actualState: GridObject.NOT_DISCOVERED

    onActualStateChanged: {
        switch(actualState) {
            case GridObject.GREYED_OUT:
                color = nothingColor
                break
            case GridObject.RADAR_DISCOVERED:
                color = radarColor
                break
            case GridObject.SHIP_DISCOVERED:
                color = shipColor
                break
            case GridObject.NOT_DISCOVERED:
            default:
                color = baseColor
        }
    }

    property bool discovered: false

    signal objectClicked()

    width: 50
    height: width
    radius: height

    Label {
        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pointSize: 24
        color: "black"

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
            if(root.actualState == GridObject.NOT_DISCOVERED)
                root.actualState = GridObject.GREYED_OUT
            else if(root.actualState == GridObject.GREYED_OUT)
                root.actualState = GridObject.NOT_DISCOVERED
        }
    }
}
