import QtQuick 2.3

// Piece element used in GembloQ. See Square.qml for comments
Item {
    id: root

    property int pointType

    Loader {
        id: loaderTop

        function loadImage() {
            if (opacity > 0 && status === Loader.Null)
                sourceComponent = componentTop
        }

        anchors.fill: root
        opacity: switch (pointType) {
                 case 0: return imageOpacity0
                 case 1: return imageOpacity180
                 case 2: return imageOpacity90
                 case 3: return imageOpacity270
                 }
        onOpacityChanged: loadImage()
        Component.onCompleted: loadImage()

        Component {
            id: componentTop

            Image {
                // Don't set antialiasing, vertex antialiasing causes unwanted
                // seams between edges of the quarter squares
                source: imageName
                sourceSize: imageSourceSize
                mipmap: true
                rotation: switch (pointType) {
                          case 1: return 180
                          case 2: return 270
                          case 3: return 90
                          default: return 0
                          }
                x: pointType == 1 || pointType == 3 ? -width / 2 : 0
            }
        }
    }
    Loader {
        function loadImage() {
            if (opacity > 0 && status === Loader.Null)
                sourceComponent = componentBottom
        }

        anchors.fill: root
        opacity: switch (pointType) {
                 case 0: return imageOpacity180
                 case 1: return imageOpacity0
                 case 2: return imageOpacity270
                 case 3: return imageOpacity90
                 }
        onOpacityChanged: loadImage()
        Component.onCompleted: loadImage()

        Component {
            id: componentBottom

            Image {
                // Don't set antialiasing, see above
                source: imageNameBottom
                sourceSize: imageSourceSize
                mipmap: true
                rotation: switch (pointType) {
                          case 1: return 180
                          case 2: return 270
                          case 3: return 90
                          default: return 0
                          }
                x: pointType == 1 || pointType == 3 ? -width / 2 : 0
            }
        }
    }
}
