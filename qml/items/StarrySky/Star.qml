import QtQuick 2.15
import QtQuick.Shapes

Shape {
    id : root

    height: 5
    width: height

    ShapePath {
        strokeWidth: 0
        strokeColor: "transparent"
        fillGradient: RadialGradient {
            centerX: width / 2; centerY: height / 2
            centerRadius: width
            focalX: centerX; focalY: centerY
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "transparent" }
        }

        startX: width / 2; startY: 0

                PathArc {
                    x: width; y: height / 2
                    radiusX: width; radiusY: height
                    direction: PathArc.Counterclockwise
                }
                PathArc {
                    x: width / 2; y: height
                    radiusX: width; radiusY: height
                    direction: PathArc.Counterclockwise
                }
                PathArc {
                    x: 0; y: height / 2
                    radiusX: width; radiusY: height
                    direction: PathArc.Counterclockwise
                }
                PathArc {
                    x: width / 2; y: 0
                    radiusX: width; radiusY: height
                    direction: PathArc.Counterclockwise
                }
    }

}
