import QtQuick 2.0

Rectangle
{
    id:buttonSelection
    radius: 12
    color: focus ? "blue":"black"
    width: parent.width/4
    height: parent.height/4
    property alias bText: keyB.text
    property alias aText: keyA.text
    property alias bBorder: borderB
    property alias aBorder: borderA
    Rectangle
    {
        id: borderB
        border.color: "yellow"
        border.width: 2
        color: "white"
        height: parent.width * .45
        width: height
        radius: height
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        Text
        {
            id: keyB
            text: ""
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: parent.height * .75
        }
    }
    Rectangle
    {
        id: borderA
        border.color: "yellow"
        border.width: 2
        color: "white"
        height: parent.width * .45
        width: height
        radius: height
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        Text
        {
            id: keyA
            text:""
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: parent.height * .75
        }
        clip: true
    }

    Keys.onReturnPressed:
    {
        sipKeyboard.currentFocus.text += keyB.text;
        sipKeyboard.inputtext += keyB.text;
    }

    Keys.onSpacePressed:
    {
        sipKeyboard.currentFocus.text += keyA.text;
        sipKeyboard.inputtext += keyA.text;
    }
}
