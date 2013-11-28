import QtQuick 2.0

Rectangle
{
    id: iconContainer
    color: "transparent"

    property string iconString: buttonText.text
    property alias source: buttonImage.source

    Image
    {
        id: buttonImage
        source: ""
        fillMode: Image.PreserveAspectFit
        height: parent.height * 0.95
        width: parent.width * 0.4
        visible: true
        anchors.leftMargin: 2
        anchors.left: parent.left
    }

    Text
    {
        id: buttonText
        height: parent.height * 0.95
        width: parent.width * 0.6
        font.pointSize: 16
        text: iconString
        color: "#b3ccee"
        anchors.leftMargin: 2
        anchors.left: buttonImage.right
        wrapMode: Text.Wrap
    }
}
