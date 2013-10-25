import QtQuick 2.0

ZoomItem {
    property alias image: image
    property alias source: image.source
    Image{
        id: image
        anchors.centerIn: parent
        anchors.fill: parent
    }
}
