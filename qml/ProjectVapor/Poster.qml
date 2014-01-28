import QtQuick 2.0

VaporRectangle
{
    id: posterContainer
    visible: false
    width: 0
    height: 0

    KeyNavigation.right: router
    KeyNavigation.left: bookshelf

    glowOpacity: 0.25
    glowZ: posterContainer.z - 50
    scalable: false

    Image
    {
        anchors.fill: posterContainer
        fillMode: Image.PreserveAspectFit
        focus: false
        source: VaporArcade.getPosterDirectory() +"/super_metroid.jpg"
        //Keys.onReturnPressed: emuLauncher.start();
    }

    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {
            emuLauncher.start("SNES", "Super Metroid.smc");
        }
        else if(event.key == Qt.Key_Backspace)
        {
            zoomsurface.zoomOut.start();
        }
    }
}
