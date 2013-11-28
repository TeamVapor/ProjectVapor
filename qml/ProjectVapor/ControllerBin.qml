import QtQuick 2.0

VaporRectangle
{
    id: controllerBinContainer
    width: 0
    height: 0
    glowOpacity: 0.25
    glowZ: -10000
    pressable: false
    scalable: false
    zScalable: false

    KeyNavigation.left: bookshelf
    KeyNavigation.up: poster
    KeyNavigation.right: router

    Image
    {
        id: controllerBinImage
        width: parent.width
        height: parent.height
        source: "qrc:/images/controller_bin.png"
        fillMode: Image.PreserveAspectFit
    }


    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {
            zoomsurface.zoomToItemCentered(controllerBin)
        }
        else if (event.key == Qt.Key_Backspace)
        {
            zoomsurface.zoomOutToFull();
        }
    }

    onZoomedInStopped: function ()
    {
        focus = true;
        settingsMenu.visible = true;
        settingsMenu.anchors.centerIn = controllerBin;
        zoomsurface.targetItem = settingsMenu;
        settingsMenu.setDefaultFocus("cont");
        vaporNavigationBar.centerIn(settingsMenu);
        vaporNavigationBar.settingsNavigationSetup();
    }

    onZoomedOutStopped: function ()
    {
        settingsMenu.visible = false;
    }
}
