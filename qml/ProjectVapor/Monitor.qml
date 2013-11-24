import QtQuick 2.0
import QtGraphicalEffects 1.0
VaporRectangle {

    width: 0
    id:monitor
    height: 0
    focus: false

    glowOpacity: 0.25
    glowZ: monitor.z - 50
    scalable: false

    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {
            zoomsurface.zoomToItemCentered(monitor)
        }
        else if(event.key == Qt.Key_Backspace)
        {
            zoomsurface.zoomOutToFull();
        }
        else if(event.key == Qt.Key_Right)
        {
            parent.parent.bookshelf.focus = true;
        }
        else if(event.key == Qt.Key_Left)
        {
            router.focus = true;
        }
    }

    Image{
        id: image
        anchors.centerIn: parent
        anchors.fill: parent
        source: "qrc:/images/monitor.png"
    }
    onZoomedInStopped: function()
    {
        focus = true;
        settingsMenu.visible = true;
        settingsMenu.anchors.centerIn = monitor;
        zoomsurface.targetItem = settingsMenu;
    }
}
