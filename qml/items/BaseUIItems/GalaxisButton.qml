import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Basic

Button {
       id: control
       text: "Button"

       contentItem: Text {
               text: control.text
               font.pixelSize: 20
               opacity: enabled ? 1.0 : 0.3
               color: "black"
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
               elide: Text.ElideRight
       }

       background: Rectangle {
           anchors.fill: parent
           color: control.down ? "orange" : "khaki"
           border.width: 0
           radius: height
       }
   }

