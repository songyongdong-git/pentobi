import QtQuick 2.0

Item {
    id: root

    property alias color: point.color
    property bool isFinal
    property bool isToPlay
    property real value
    property real bonus
    property real pointSize

    Rectangle {
        id: point

        width: (isToPlay ? 1.3 : 1) * pointSize
        border {
            color: Qt.lighter(color, theme.toPlayColorLighter)
            width: isToPlay ? Math.max(0.15 * pointSize, 1) : 0
        }
        height: width
        radius: width / 2
        anchors.verticalCenter: root.verticalCenter
    }
    Text {
        id: scoreText

        text: ! isFinal ?
                  "%L1".arg(value) :
                  "%1<u>%L2</u>".arg(bonus > 0 ? "*" : "").arg(value)
        color: theme.fontColorScore
        anchors {
            left: point.right
            leftMargin: (isToPlay ? 0.2 : 0.4) * point.width
            verticalCenter: root.verticalCenter
        }
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 1.4 * pointSize
    }
}
