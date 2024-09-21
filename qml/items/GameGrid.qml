import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import GalaxisGrid

Grid {
    id: root

    rows: GalaxisGrid.getGridHeight()
    columns: GalaxisGrid.getGridWidth()

    rowSpacing: (height - (50 * rows)) / (rows)
    columnSpacing: (width - (50 - columns)) /(columns + 1)

    flow: Grid.TopToBottom

    Component.onCompleted: {
        var counter = 0
        console.log("Columns : ", columns, " Rows : ", rows)
        for(var i = 0; i < columns; i++) {
            for(var j = 0; j < rows; j++) {
                console.log("Set x : ", i, " j : ", j)
                gridRepeater.itemAt(counter).gridX = i
                gridRepeater.itemAt(counter).gridY = j
                counter++
            }
        }
    }

    Repeater {
        id: gridRepeater

        anchors.fill: parent

        model: root.rows * root.columns

        TestGridObject {
            id: delegate

            Layout.alignment: Layout.Center

            onObjectClicked: {
                beaconNumber = GalaxisGrid.beaconCall(gridX, gridY)
                if(GalaxisGrid.isShip(gridX, gridY))
                    color = "salmon"
                else
                    color = "lemonchiffon"
            }

            Label {
                id: testLabel

                anchors.top: parent.bottom
                text: parent.gridX + " - " + parent.gridY
            }

            Timer {
                id: testTimer
                interval: 1000
                running: false
                repeat: false
                onTriggered: {
                    if(GalaxisGrid.isShip(gridX, gridY)) {
                        color = "salmon"
                    }
                }
            }
        }
    }
}
