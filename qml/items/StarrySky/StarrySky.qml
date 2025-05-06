import QtQuick 2.15

Rectangle {
    id: root

    property int starNumber: 200

    function getRandomInt(max) {
      return Math.floor(Math.random() * max - 1) + 1;
    }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "midnightblue" }
        GradientStop { position: 1.0; color: "darkslateblue" }
    }

    Repeater {
        id: starRepeater

        model: starNumber

        Star {
            height: getRandomInt(10)
            x: getRandomInt(root.width)
            y: getRandomInt(root.height)
            glitterTime: 200 + getRandomInt(800)
            transparentTime: 5000 + getRandomInt(1500)
        }
    }

}
