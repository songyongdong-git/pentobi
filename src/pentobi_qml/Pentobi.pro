TEMPLATE = app

QT += qml quick svg concurrent

INCLUDEPATH += ..
CONFIG += c++11
QMAKE_CXXFLAGS += -DPENTOBI_LOW_RESOURCES
QMAKE_CXXFLAGS_DEBUG += -DLIBBOARDGAME_DEBUG
gcc {
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE -= -Os
    QMAKE_CXXFLAGS_RELEASE *= -O3 -ffast-math
}

SOURCES += \
    BoardModel.cpp \
    Main.cpp \
    PieceModel.cpp \
    PlayerModel.cpp \
    ../libboardgame_base/CoordPoint.cpp \
    ../libboardgame_base/Rating.cpp \
    ../libboardgame_base/SpShtStrRep.cpp \
    ../libboardgame_base/Transform.cpp \
    ../libboardgame_sys/Memory.cpp \
    ../libboardgame_sgf/MissingProperty.cpp \
    ../libboardgame_sgf/Reader.cpp \
    ../libboardgame_sgf/TreeIterator.cpp \
    ../libboardgame_sgf/TreeReader.cpp \
    ../libboardgame_sgf/TreeWriter.cpp \
    ../libboardgame_sgf/Writer.cpp \
    ../libboardgame_util/Abort.cpp \
    ../libboardgame_util/Assert.cpp \
    ../libboardgame_util/Barrier.cpp \
    ../libboardgame_util/Exception.cpp \
    ../libboardgame_util/FastLog.cpp \
    ../libboardgame_util/IntervalChecker.cpp \
    ../libboardgame_util/Log.cpp \
    ../libboardgame_util/Options.cpp \
    ../libboardgame_util/RandomGenerator.cpp \
    ../libboardgame_util/StringUtil.cpp \
    ../libboardgame_util/TimeIntervalChecker.cpp \
    ../libboardgame_util/Timer.cpp \
    ../libboardgame_util/TimeSource.cpp \
    ../libpentobi_mcts/AnalyzeGame.cpp \
    ../libpentobi_mcts/LocalValue.cpp \
    ../libpentobi_mcts/PriorKnowledge.cpp \
    ../libpentobi_mcts/Search.cpp \
    ../libpentobi_mcts/State.cpp \
    ../libpentobi_mcts/Util.cpp \
    ../libpentobi_base/Board.cpp \
    ../libpentobi_base/BoardConst.cpp \
    ../libpentobi_base/BoardUpdater.cpp \
    ../libpentobi_base/BoardUtil.cpp \
    ../libpentobi_base/Book.cpp \
    ../libpentobi_base/Color.cpp \
    ../libpentobi_base/Game.cpp \
    ../libpentobi_base/GameStateHistory.cpp \
    ../libpentobi_base/NodeUtil.cpp \
    ../libpentobi_base/PieceInfo.cpp \
    ../libpentobi_base/PieceTransforms.cpp \
    ../libpentobi_base/PieceTransformsClassic.cpp \
    ../libpentobi_base/PieceTransformsTrigon.cpp \
    ../libpentobi_base/PointState.cpp \
    ../libpentobi_base/PentobiSgfUtil.cpp \
    ../libpentobi_base/StartingPoints.cpp \
    ../libpentobi_base/SymmetricPoints.cpp \
    ../libpentobi_base/TreeUtil.cpp \
    ../libpentobi_base/Variant.cpp \
    ../libpentobi_base/PlayerBase.cpp \
    ../libboardgame_sgf/SgfNode.cpp \
    ../libboardgame_sgf/SgfTree.cpp \
    ../libpentobi_base/PentobiTree.cpp \
    ../libpentobi_base/PentobiTreeWriter.cpp \
    ../libboardgame_util/WallTimeSource.cpp \
    ../libboardgame_util/CpuTimeSource.cpp \
    ../libpentobi_mcts/StateUtil.cpp \
    ../libpentobi_mcts/Player.cpp \
    ../libboardgame_sgf/SgfUtil.cpp \
    ../libboardgame_sys/CpuTime.cpp

RESOURCES += \
    resources.qrc \
    ../books/pentobi_books.qrc

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    BoardModel.h \
    PieceModel.h \
    PlayerModel.h \
    ../libboardgame_sys/Compiler.h \
    ../libboardgame_sys/Memory.h \
    ../libpentobi_mcts/AnalyzeGame.h \
    ../libpentobi_mcts/Float.h \
    ../libpentobi_mcts/LocalValue.h \
    ../libpentobi_mcts/PriorKnowledge.h \
    ../libpentobi_mcts/Search.h \
    ../libpentobi_mcts/State.h \
    ../libpentobi_mcts/Util.h \
    ../libboardgame_sgf/InvalidPropertyValue.h \
    ../libboardgame_sgf/InvalidTree.h \
    ../libboardgame_sgf/MissingProperty.h \
    ../libboardgame_sgf/Reader.h \
    ../libboardgame_sgf/TreeIterator.h \
    ../libboardgame_sgf/TreeReader.h \
    ../libboardgame_sgf/TreeWriter.h \
    ../libboardgame_sgf/Writer.h \
    ../libboardgame_util/Abort.h \
    ../libboardgame_util/ArrayList.h \
    ../libboardgame_util/Assert.h \
    ../libboardgame_util/Barrier.h \
    ../libboardgame_util/BitMarker.h \
    ../libboardgame_util/Exception.h \
    ../libboardgame_util/FastLog.h \
    ../libboardgame_util/FmtSaver.h \
    ../libboardgame_util/IntervalChecker.h \
    ../libboardgame_util/Log.h \
    ../libboardgame_util/MathUtil.h \
    ../libboardgame_util/NullElement.h \
    ../libboardgame_util/NullTermList.h \
    ../libboardgame_util/Options.h \
    ../libboardgame_util/RandomGenerator.h \
    ../libboardgame_util/Statistics.h \
    ../libboardgame_util/StringUtil.h \
    ../libboardgame_util/TimeIntervalChecker.h \
    ../libboardgame_util/Timer.h \
    ../libboardgame_util/TimeSource.h \
    ../libboardgame_util/Unused.h \
    ../libpentobi_base/AdjDiagIterator.h \
    ../libpentobi_base/AdjIterator.h \
    ../libpentobi_base/Board.h \
    ../libpentobi_base/BoardConst.h \
    ../libpentobi_base/BoardUpdater.h \
    ../libpentobi_base/BoardUtil.h \
    ../libpentobi_base/Book.h \
    ../libpentobi_base/Color.h \
    ../libpentobi_base/ColorMap.h \
    ../libpentobi_base/ColorMove.h \
    ../libpentobi_base/DiagIterator.h \
    ../libpentobi_base/Game.h \
    ../libpentobi_base/GameStateHistory.h \
    ../libpentobi_base/Geometry.h \
    ../libpentobi_base/Grid.h \
    ../libpentobi_base/Marker.h \
    ../libpentobi_base/Move.h \
    ../libpentobi_base/MoveInfo.h \
    ../libpentobi_base/MoveList.h \
    ../libpentobi_base/MoveMarker.h \
    ../libpentobi_base/MovePoints.h \
    ../libpentobi_base/NodeUtil.h \
    ../libpentobi_base/Piece.h \
    ../libpentobi_base/PieceInfo.h \
    ../libpentobi_base/PieceMap.h \
    ../libpentobi_base/PieceTransforms.h \
    ../libpentobi_base/PieceTransformsClassic.h \
    ../libpentobi_base/PieceTransformsTrigon.h \
    ../libpentobi_base/Point.h \
    ../libpentobi_base/PointList.h \
    ../libpentobi_base/PointState.h \
    ../libpentobi_base/PrecompMoves.h \
    ../libpentobi_base/Setup.h \
    ../libpentobi_base/PentobiSgfUtil.h \
    ../libpentobi_base/StartingPoints.h \
    ../libpentobi_base/SymmetricPoints.h \
    ../libpentobi_base/TreeUtil.h \
    ../libpentobi_base/Variant.h \
    ../libboardgame_base/CoordPoint.h \
    ../libboardgame_base/Geometry.h \
    ../libboardgame_base/GeometryUtil.h \
    ../libboardgame_base/Grid.h \
    ../libboardgame_base/Marker.h \
    ../libboardgame_base/Point.h \
    ../libboardgame_base/PointList.h \
    ../libboardgame_base/PointTransform.h \
    ../libboardgame_base/Rating.h \
    ../libboardgame_base/RectGeometry.h \
    ../libboardgame_base/SpShtStrRep.h \
    ../libboardgame_base/Transform.h \
    ../libboardgame_base/TrigonGeometry.h \
    ../libpentobi_base/PlayerBase.h \
    ../libboardgame_mcts/Atomic.h \
    ../libboardgame_mcts/BiasTerm.h \
    ../libboardgame_mcts/ChildIterator.h \
    ../libboardgame_mcts/LastGoodReply.h \
    ../libboardgame_mcts/Node.h \
    ../libboardgame_mcts/PlayerMove.h \
    ../libboardgame_mcts/SearchBase.h \
    ../libboardgame_mcts/Tree.h \
    ../libboardgame_mcts/TreeUtil.h \
    ../libboardgame_sgf/SgfNode.h \
    ../libboardgame_sgf/SgfTree.h \
    ../libpentobi_base/PentobiTree.h \
    ../libpentobi_base/PentobiTreeWriter.h \
    ../libboardgame_util/WallTimeSource.h \
    ../libboardgame_util/CpuTimeSource.h \
    ../libpentobi_mcts/StateUtil.h \
    ../libpentobi_mcts/Player.h \
    ../libboardgame_sgf/SgfUtil.h \
    ../libboardgame_sys/CpuTime.h

OTHER_FILES += \
    android/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android