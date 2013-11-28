import QtQuick 2.0

//refactor restart
VaporRectangle
{
    id: settingsContainer
    width: 0
    height: 0
    color: base
    visible: false

    function setDefaultFocus (setTab)
    {
        navigationTabContainer.focus = true;
        if (setTab == "app")
            appTab.openTab = true;
        else if (setTab == "emu")
            emuTab.openTab = true;
        else if (setTab == "cont")
            contTab.openTab = true;
    }

    VaporRectangle
    {
        id: navigationTabContainer
        height: parent.height
        width: parent.width * 0.05
        anchors.left: parent.left
        color: alternateBase
        focus: false

        scalable: false
        pressable: false

        Keys.onReturnPressed: appTab.focus = true;

        Column
        {
            id: navigationTabPositioner
            anchors.fill: parent

            VaporVerticalTab
            {
                id: appTab
                height: parent.height / 3
                width: parent.width
                tabText: "Application Settings"

                KeyNavigation.down: emuTab
                KeyNavigation.up: contTab

                Keys.onPressed:
                {
                    if (event.key == Qt.Key_Return)
                    {
                        appTab.openTab = true;
                        emuTab.openTab = false;
                        contTab.openTab = false;
                    }
                    else if (event.key == Qt.Key_Backspace)
                    {
                        focus = false;
                        navigationTabContainer.focus = true;
                    }
                }
            }
            VaporVerticalTab
            {
                id: emuTab
                height: parent.height / 3
                width: parent.width
                tabText: "Emulator Settings"

                KeyNavigation.up: appTab
                KeyNavigation.down: contTab

                Keys.onPressed:
                {
                    if (event.key == Qt.Key_Return)
                    {
                        appTab.openTab = false;
                        emuTab.openTab = true;
                        contTab.openTab = false;
                    }
                    else if (event.key == Qt.Key_Backspace)
                    {
                        focus = false;
                        navigationTabContainer.focus = true;
                    }
                }
            }
            VaporVerticalTab
            {
                id: contTab
                height: parent.height / 3
                width: parent.width
                tabText: "Controller Settings"

                KeyNavigation.up: emuTab
                KeyNavigation.down: appTab

                Keys.onPressed:
                {
                    if (event.key == Qt.Key_Return)
                    {
                        appTab.openTab = false;
                        emuTab.openTab = false;
                        contTab.openTab = true;
                    }
                    else if (event.key == Qt.Key_Backspace)
                    {
                        focus = false;
                        navigationTabContainer.focus = true;
                    }
                }
            }
        }
    }

    function resetTabSelection()
    {
        appTab.openTab = false;
        emuTab.openTab = false;
        contTab.openTab = false;
    }

    onVisibleChanged:
    {
        if (visible == false)
        {
            vaporNavigationBar.centerIn(zoomsurface);
            vaporNavigationBar.homeScreenNavigationSetup();
        }
        else if (visible == true)
        {

        }
    }

    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {

        }
        else if (event.key == Qt.Key_Backspace)
        {
            resetTabSelection();
            settingsContainer.visible = false;
            zoomsurface.zoomOutToFull();
            monitor.focus = true;
        }
    }

    onZoomedOutStopped: function ()
    {
        settingsContainer.visible = false;
    }
}
