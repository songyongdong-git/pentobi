import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "Main.js" as Logic

FileDialog {
    title: qsTr("Save")
    selectExisting: false
    folder: root.folder != "" ? root.folder : (isAndroid ? "file:///sdcard" : shortcuts.desktop)
    nameFilters: [ qsTr("Blokus games (*.blksgf)"), qsTr("All files (*)") ]
    onAccepted: {
        root.folder = folder
        queuedSaveFileUrl.file = Logic.getFileFromUrl(fileUrl)
        queuedSaveFileUrl.restart()
    }
    onVisibleChanged:
        if (! visible) {
            // We always create a new save file dialog because currently there
            // is no way to initialize the default file in FileDialog and we
            // don't want the dialog to default to the last file saved, which
            // might be different from the currently loaded file.
            saveDialog.source = ""
            gameDisplay.forceActiveFocus() // QTBUG-48456
        }
}
