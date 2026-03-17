import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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

    property bool gamePaused: false

    function pauseGame(victory) {
        if(gamePaused) {
            console.log("Game already paused")
            return
        }

        if(victory)
            pauseDialog.victoryMode()
        else
            pauseDialog.pauseMode()

        gameGrid.deactivateGrid()
        pauseDialog.visible = true
        gamePaused = true
    }

    function resumeGame() {
        if(!gamePaused) {
            console.log("Game already active")
            return
        }

        gameGrid.activateGrid()
        pauseDialog.visible = false
        gamePaused = false
    }

    Connections {
        target: GalaxisGrid

        function onVictory() {
            root.pauseGame(true)
        }

        function onScoreChanged() {
            scoreLabel.text = "Score : " + GalaxisGrid.score
        }
    }

    Shortcut {
        sequence: "Esc"
        onActivated: {
            if(!gamePaused)
                root.pauseGame(false)
            else
                root.resumeGame(false)
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

        function activateGrid() {
            opacity = 1
            enabled = true
        }

        function deactivateGrid() {
            opacity = 0.5
            enabled = false
        }
    }

    Rectangle {
        id: pauseDialog

        anchors.fill: parent

        color: "transparent"
        border.width: 0

        visible: false

        function pauseMode() {
            pauseLabel.text = "Pause"
            resumeButton.visible = true
        }

        function victoryMode() {
            pauseLabel.text = "Vous avez gagné !"
            resumeButton.visible = false
        }

        Label {
            id: pauseLabel

            anchors.centerIn: parent

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pointSize: 96
            color: "lavender"

            text: "Pause"
        }

        Label {
            id: scoreLabel

            anchors.top: pauseLabel.bottom
            anchors.topMargin: 7
            anchors.horizontalCenter: parent.horizontalCenter

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pointSize: 24
            color: "plum"

            text: "Score : " + GalaxisGrid.score
        }

        RowLayout {
            id: pauseButtonsLayout

            anchors.top: scoreLabel.bottom
            anchors.topMargin: 7
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 5

            GalaxisButton {
                id: resumeButton

                text: "Reprendre"

                onClicked: {
                    root.resumeGame()
                }
            }

            GalaxisButton {
                id: newGameButton

                text: "Nouvelle partie"

                onClicked: {
                    GalaxisGrid.gameStart()
                    gameGrid.init()
                    root.resumeGame()
                }
            }

            GalaxisButton {
                id: backToMenuButton

                text: "Retour au Menu"

                onClicked: {
                    gamePageUiLink.backToMainMenu()
                }
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
