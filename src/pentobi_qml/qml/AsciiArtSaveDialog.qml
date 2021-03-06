import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "Main.js" as Logic

FileDialog {
    title: qsTr("Export ASCII Art")
    selectExisting: false
    folder: root.folder === "" ? shortcuts.desktop : root.folder
    nameFilters: [ qsTr("Text files (*.txt)"), qsTr("All files (*)") ]
    onAccepted: {
        Logic.exportAsciiArt(fileUrl)
        root.folder = folder
    }
    onVisibleChanged: if (! visible) gameDisplay.forceActiveFocus() // QTBUG-48456
}
