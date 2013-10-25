import QtQuick 2.0
import QtGraphicalEffects 1.0
ZoomItem {

    width: 0
    id:monitor
    height: 0
    focus: false
    Glow
    {
        anchors.centerIn: monitor
        color: "yellow"
        width: monitor.width *1.01
        height: monitor.height *1.01
        source:image
        samples:10
        radius: 8
        spread: 1.0
        visible: monitor.focus
        enabled: monitor.focus
    }
    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {
            zoomsurface.zoomToItemCentered(monitor)
        }
        else if(event.key == Qt.Key_Backspace)
        {
            zoomsurface.zoomOut.start();
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
