import QtQuick 2.0
import QtQuick.Controls 1.1
import "GameDisplay.js" as Logic

Item
{
    id: gameDisplay // Referenced by Piece*.qml

    property var pickedPiece: null
    property bool markLastMove: true
    property bool enableAnimations: true
    property alias busyIndicatorRunning: busyIndicator.running
    property size imageSourceSize: {
        var width = board.gridWidth, height = board.gridHeight
        if (board.isTrigon)
            return Qt.size(2 * width, height)
        if (board.isNexos)
            return Qt.size(1.5 * width, 1.5 * height)
        if (board.isCallisto)
            return Qt.size(0.9 * width, 0.9 * height)
        return Qt.size(width, height)
    }
    property alias pieces0: pieceSelector.pieces0
    property alias pieces1: pieceSelector.pieces1
    property alias pieces2: pieceSelector.pieces2
    property alias pieces3: pieceSelector.pieces3

    signal play(var pieceModel, point gameCoord)

    function createPieces() { Logic.createPieces() }
    function destroyPieces() { Logic.destroyPieces() }
    function showToPlay() { pieceSelector.contentY = 0 }
    function showMoveHint(move) { Logic.showMoveHint(move) }

    onWidthChanged: pickedPiece = null
    onHeightChanged: pickedPiece = null

    Column {
        id: column

        width: gameDisplay.width
        anchors.centerIn: gameDisplay
        spacing: 0.01 * board.width

        Board {
            id: board

            gameVariant: gameModel.gameVariant
            width: Math.min(
                       parent.width,
                       gameDisplay.height / (1.08 + 2.7 / pieceSelector.columns))
            height: isTrigon ? Math.sqrt(3) / 2 * width : width
            anchors.horizontalCenter: parent.horizontalCenter
        }
        ScoreDisplay {
            id: scoreDisplay

            gameVariant: gameModel.gameVariant
            points0: gameModel.points0
            points1: gameModel.points1
            points2: gameModel.points2
            points3: gameModel.points3
            bonus0: gameModel.bonus0
            bonus1: gameModel.bonus1
            bonus2: gameModel.bonus2
            bonus3: gameModel.bonus3
            hasMoves0: gameModel.hasMoves0
            hasMoves1: gameModel.hasMoves1
            hasMoves2: gameModel.hasMoves2
            hasMoves3: gameModel.hasMoves3
            toPlay: gameModel.isGameOver ? -1 : gameModel.toPlay
            altPlayer: gameModel.altPlayer
            height: 0.06 * board.width
            pointSize: 0.5 * height
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Flickable {
            id: flickable

            width: 0.9 * board.width
            height: width / pieceSelector.columns * pieceSelector.rows
            contentWidth: 2 * width
            contentHeight: height
            anchors.horizontalCenter: board.horizontalCenter
            clip: true
            onMovementEnded: {
                snapAnimation.to = contentX > width / 2 ? width : 0
                snapAnimation.restart()
            }

            Row {
                id: flickableContent

                PieceSelector {
                    id: pieceSelector

                    columns: gameModel.gameVariant.indexOf("classic") == 0
                             || gameModel.gameVariant.indexOf("callisto") == 0
                             || gameModel.gameVariant == "duo" ? 7 : 8
                    width: flickable.width
                    height: flickable.height
                    rows: 3
                    gameVariant: gameModel.gameVariant
                    toPlay: gameModel.toPlay
                    nuColors: gameModel.nuColors
                    transitionsEnabled: false
                    onPiecePicked: Logic.pickPiece(piece)
                }
                NavigationPanel {
                    width: flickable.width
                    height: flickable.height
                }
            }
            SmoothedAnimation {
                id: snapAnimation

                target: flickable
                property: "contentX"
                duration: 200
            }
        }
    }
    BusyIndicator {
        id: busyIndicator

        x: (gameDisplay.width - width) / 2
        y: column.y + flickable.y + (flickable.height - height) / 2
    }
    PieceManipulator {
        id: pieceManipulator

        legal: {
            if (pickedPiece === null)
                return false
            // Don't use mapToItem(board, width / 2, height / 2), we want a
            // dependency on x, y.
            var pos = parent.mapToItem(board, x + width / 2, y + height / 2)
            return gameModel.isLegalPos(pickedPiece.pieceModel,
                                        pickedPiece.pieceModel.state,
                                        board.mapToGame(pos))
        }
        width: 0.6 * board.width; height: width
        visible: pickedPiece !== null
        pieceModel: pickedPiece !== null ? pickedPiece.pieceModel : null
        onPiecePlayed: {
            var pos = mapToItem(board, width / 2, height / 2)
            if (! board.contains(Qt.point(pos.x, pos.y)))
                pickedPiece = null
            else if (legal)
                play(pieceModel, board.mapToGame(pos))
        }
    }
    Connections {
        target: gameModel
        onPositionChanged: pickedPiece = null
    }
}
