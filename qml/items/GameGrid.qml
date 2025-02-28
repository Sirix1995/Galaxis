import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import GalaxisGrid

Grid {
    id: root

    rows: GalaxisGrid.getGridHeight()
    columns: GalaxisGrid.getGridWidth()

    rowSpacing: (height - (50 * rows)) / (rows)
    columnSpacing: (width - (50 - columns)) /(columns + 6)

    flow: Grid.TopToBottom

    Component.onCompleted: {
        var counter = 0

        //console.log("Columns : ", columns, " Rows : ", rows)
        for(var i = 0; i < columns; i++) {
            for(var j = 0; j < rows; j++) {
                //console.log("Set x : ", i, " j : ", j)
                gridRepeater.itemAt(counter).gridX = i
                gridRepeater.itemAt(counter).gridY = j
                counter++
            }
        }
    }

    function init() {
        var counter = 0
        for(var i = 0; i < columns; i++) {
            for(var j = 0; j < rows; j++) {
                gridRepeater.itemAt(counter).actualState = GridObject.NOT_DISCOVERED
                gridRepeater.itemAt(counter).beaconNumber = 6
                counter++
            }
        }
    }

    Repeater {
        id: gridRepeater

        anchors.fill: parent

        model: root.rows * root.columns

        GridObject {
            id: delegate

            Layout.alignment: Layout.Center

            onObjectClicked: {
                beaconNumber = GalaxisGrid.beaconCall(gridX, gridY)
                if(GalaxisGrid.isShip(gridX, gridY))
                    actualState = GridObject.SHIP_DISCOVERED
                else
                    actualState = GridObject.RADAR_DISCOVERED
            }

            Label {
                id: testLabel

                anchors.top: parent.bottom
                visible: false
                text: parent.gridX + " - " + parent.gridY
            }
        }
    }
}
