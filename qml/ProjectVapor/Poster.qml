import QtQuick 2.0
import com.vapor.project 1.0

ZoomItem
{
    id: posterContainer
    visible: false
    width: 0
    height: 0

    property alias emuLauncher: emuLauncher

    KeyNavigation.right: router
    KeyNavigation.left: bookshelf

    EmulatorLauncher
    {
        id:emuLauncher
    }

    Image
    {
        anchors.fill: posterContainer
        fillMode: Image.PreserveAspectFit
        focus: false
        source: "qrc:/images/super_metroid.jpg"
        Keys.onReturnPressed: emuLauncher.start();
    }

    Rectangle
    {
        id: posterSelected
        width: parent.width
        height: parent.height
        color: "transparent"
        border.width: 6
        border.color: "gold"
        visible: parent.focus
        radius: 8
    }

    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {
            emuLauncher.start();
        }
        else if(event.key == Qt.Key_Backspace)
        {
            zoomsurface.zoomOut.start();
        }
    }
}
