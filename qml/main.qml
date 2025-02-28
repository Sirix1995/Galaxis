import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import "./style/"
import "items"
import "items/StarrySky"

import GalaxisGrid

AppRectangle {
    id: root

    width: 1024
    height: 468


    Connections {
        target: GalaxisGrid

        onVictory: {
            gameGrid.opacity = 0.5
            gameGrid.enabled = false
            victoryLabel.visible = true
        }
    }

    StarrySky {
        id: background

        anchors.fill: parent

    }

    GameGrid {
        id: gameGrid
        anchors.fill: parent
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
    }

    Label {
        id: victoryLabel

        anchors.centerIn: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pointSize: 96
        visible: false
        color: "lavender"

        text: "Vous avez gagné !"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
