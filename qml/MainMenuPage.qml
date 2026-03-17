import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

import "./style/"
import "./items/"
import "items/BaseUIItems"

AppRectangle {
    id: root

    width: 1024
    height: 468

    Rectangle {
        id: background

        anchors.fill: parent

        color: "silver"
    }

    Image {
        id: logoImage

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        source: "qrc:/Images/ravensburger-1980 - -galaxis-electronic - -jeu-spatial-electronique-p-image-373396-grande.jpg - copie.png"
    }

    ColumnLayout {
        id: menuLayout

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: logoImage.bottom
        anchors.topMargin: 30

        spacing: 10

        width: parent.width * 0.6

        GalaxisButton {
            id: soloGameButton

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            text: "Nouvelle partie Solo"

            onClicked: MainMenuUiLink.newSoloGame()
        }

        GalaxisButton {
            id: multiGameButton

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            text: "Nouvelle partie Multijoueur"

            enabled: false

            onClicked: MainMenuUiLink.newSoloGame()
        }

        GalaxisButton {
            id: scoresButton

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            text: "Meilleurs Scores"

            enabled: false

            onClicked: MainMenuUiLink.newSoloGame()
        }

        GalaxisButton {
            id: quitButton

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            text: "Quitter"

            onClicked: MainMenuUiLink.quitApplication()
        }
    }

}
