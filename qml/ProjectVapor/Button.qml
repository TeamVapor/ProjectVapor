import QtQuick 2.0

Rectangle
{
    id: button
    property string text: ""
//    property real fontSize: parent.width / 32

    signal clicked


    border { width: 1; color: Qt.darker(activePalette.button) }
    antialiasing: true
    radius: 8

    gradient: Gradient
    {
        GradientStop { position: 0.0;
                        color:
                        {
                            if (mouseArea.pressed)
                                return activePalette.dark
                            else
                                return activePalette.light
                        }
                      }
        GradientStop { position: 1.0; color: activePalette.button }
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        onClicked: button.clicked();
    }

    Keys.onReturnPressed: button.clicked();

    Text
    {
        id: buttonLabel
        anchors.centerIn: button
        color: activePalette.buttonText
        font.pixelSize: button.width / 8
        text: button.text
    }
}
