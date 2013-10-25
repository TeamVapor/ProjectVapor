import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

ZoomItem
{
    id: settingsContainer
    SystemPalette{id: activePalette}
    color: activePalette.midlight


    Keys.onEscapePressed:
    {
        //visible = false;
        zoomsurface.zoomOut.start();
    }

    Rectangle
    {
        id: emuVideoSettings
        width: settingsContainer.width / 2
        height: settingsContainer.height
        color: activePalette.dark
        //anchors.top: settingsContainer.top
        anchors.left: emuDisplaySettings.right
        anchors.margins: 4
        Text
        {
            id: emuVideoSettingsTitle
            height: parent.height/10
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Video Settings"
            font.pixelSize: height * .9
        }
/*
; Video Mode [0..22]
;   0 = 256x224      R WIN     1 = 256x224      R FULL
;   2 = 512x448     DR WIN     3 = 512x448     DR FULL
;   4 = 640x480     DR FULL
;   5 = 256x224    O R WIN     6 = 512x448    ODR WIN
;   7 = 640x480    ODS FULL    8 = 640x480    ODS WIN
;   9 = 640x560    ODR WIN    10 = 768x672    ODR WIN
;  11 = 800x600    ODS FULL   12 = 800x600    ODS WIN
;  13 = 896x784    ODR WIN    14 = 1024x768   ODS FULL
;  15 = 1024x768   ODS WIN    16 = 1024x896   ODR WIN
;  17 = 1280x960   ODS FULL   18 = 1280x1024  ODS FULL
;  19 = 1600x1200  ODS FULL   20 = VARIABLE   ODR WIN
;  21 = VARIABLE   ODS WIN    22 = CUSTOM     OD  FULL
*/
            ComboBox
            {
                id: emuResSetting
                model: ["0: 256x224 R WIN", "1: 256x224 R FULL",
                    "2: 512x448 DR WIN", "3: 512x448 DR FULL",
                    "4: 640x480 DR FULL", "5: 256x224 O R WIN",
                    "6: 512x448 ODR WIN", "7: 640x480 ODS FULL",
                    "8: 640x480 ODS WIN", "9: 640x560 ODR WIN",
                    "10: 768x672 ODR WIN", "11: 800x600 ODS FULL",
                    "12: 800x600 ODS WIN", "13: 896x784 ODR WIN",
                    "14: 1024x768 ODS FULL", "15: 1024x768 ODS WIN",
                    "16: 1024x896 ODR WIN", "17: 1280x960 ODS FULL",
                    "18: 1280x1024 ODS FULL","19: 1600x1200 ODS FULL",
                    "20: VARIABLE ODR WIN","21: VARIABLE ODS WIN",
                    "22: CUSTOM OD FULL"]
                anchors.top: emuVideoSettingsTitle.bottom
                anchors.margins: 4
                width: parent.width / 4
                height: parent.height / 16
            }
    }

    Rectangle
    {
        id: emuDisplaySettings
        width: settingsContainer.width / 2
        height: settingsContainer.height
        color: activePalette.dark
        anchors.top: settingsContainer.top
        anchors.left: settingsContainer.left
        anchors.margins: 4
        Text
        {
            id: emuDisplaySettingsTitle
            height: parent.height/10
            text: "Display Info Settings"
            font.pixelSize: height * .75
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Column
        {
            anchors.top: emuDisplaySettingsTitle.bottom
            anchors.left: parent.left
            anchors.margins: 4
            height: parent.height/8
            spacing: 4
            CheckBox
            {
                height: parent.height / 5
                //width: parent.width
                id: romInfoCheckBox
                text: "Display rom info on load."
            }
            CheckBox
            {
                height: parent.height / 5
                //width: parent.width
                id: fpsDisplayCheckBox
                text: "Display emulator FPS."
            }
            CheckBox
            {
                height: parent.height / 5
                //width: parent.width
                id: clockDisplayCheckBox
                text: "Display system time."
            }
            CheckBox
            {
                visible: clockDisplayCheckBox.checked
                height: parent.height / 5
                //width: parent.width
                anchors.left: clockDisplayCheckBox.right
                id: twelveHourDisplayCheckBox
                text: "Display as 12 hour time."
            }
            CheckBox
            {
                visible: clockDisplayCheckBox.checked
                height: parent.height / 5
                //width: parent.width
                anchors.left: clockDisplayCheckBox.right
                id: clockBoxDisplayCheckBox
                text: "Display clock box time."
            }
        }
    }

    onZoomedOutStopped: function ()
    {
        visible = false;
        monitor.focus = true;
    }
}
