import QtQuick 2.0
import QtGraphicalEffects 1.0
ZoomItem {

    width: 0
    id:router
    height: 0
    focus: false

    KeyNavigation.left: poster

    Glow
    {
        anchors.centerIn: router
        color: "yellow"
        width: router.width *1.01
        height: router.height *1.01
        source:image
        samples:10
        radius: 8
        spread: 1.0
        visible: router.focus
        enabled: router.focus
    }
    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return) {
            zoomsurface.zoomToItemCentered(router);
        }
        else if(event.key == Qt.Key_Backspace) {
            zoomsurface.zoomOut.start();
        }
        else if(event.key == Qt.Key_Right) {
            monitor.focus = true;
        }
    }

    Image{
        id: image
        anchors.centerIn: parent
        anchors.fill: parent
        source: "qrc:/images/router.png"
    }
    onZoomedInStopped: function()
    {
        focus = true;
        netLobby.visible = true;
        netLobby.anchors.centerIn = router;
        netLobby.setDefaultFocus();
        zoomsurface.targetItem = netLobby;
    }
}
