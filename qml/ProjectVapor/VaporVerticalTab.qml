import QtQuick 2.0

VaporRectangle
{
    id: tabContainer
    color: selected ? dark : mid
    visible: true
    scalable: false
    pressable: true
    focus: false

    border.width: 8
    border.color: shadow

    radius: 4

    property string tabText: ""
    property alias openTab: tabContainer.selected

    Text
    {
        id: tabLabel
        anchors.centerIn: parent
        font.pointSize: 16
        color: tabContainer.light
        rotation: -90
        text: tabText
    }
}
