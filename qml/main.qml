import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

import QtQuick.Controls.Basic

import "./style/"
import "items"
import "items/StarrySky"
import "items/BaseUIItems"

import GalaxisGrid

AppRectangle {
    id: root

    width: 1024
    height: 468


    Connections {
        target: GalaxisGrid

        function onVictory() {
            gameGrid.opacity = 0.5
            gameGrid.enabled = false
            victoryLabel.visible = true
            newGameButton.visible = true
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

    GalaxisButton {
        id: newGameButton

        anchors.top: victoryLabel.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        height: 50
        width: 200

        visible: false

        text: "Nouvelle partie"

        onClicked: {
            GalaxisGrid.gameStart()
            gameGrid.init()
            victoryLabel.visible = false
            visible = false
            gameGrid.opacity = 1
            gameGrid.enabled = true
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
