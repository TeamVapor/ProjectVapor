import QtQuick 2.0

VaporRectangle
{
    id: button
    property string text: ""
    signal clicked
    gradient: Gradient
    {
        GradientStop { position: 0.00;
            color:
            {
                if (mouseArea.pressed)
                    return "lightsteelblue"
                else
                    return "#56699e"
            }
        }
        GradientStop { position: 1.00; color: "#3e4364"; }
    }
    border.width: 3
    border.color: "#3e4b8d"
    antialiasing: true

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
        color: "black"
        font.pixelSize: button.width / 8
        text: button.text
    }
}
