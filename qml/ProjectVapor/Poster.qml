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

    glowOpacity: 0.25
    glowZ: posterContainer.z - 50
    scalable: false

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
