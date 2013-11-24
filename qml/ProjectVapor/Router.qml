import QtQuick 2.0
import QtGraphicalEffects 1.0
VaporRectangle {

    width: 0
    id:router
    height: 0
    focus: false

    KeyNavigation.left: poster

    glowOpacity: 0.25
    glowZ: -10000
    scalable: false

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
