import QtQuick 2.1
import QtQuick.Window 2.0
Rectangle {
    id: homeScreen
    width: Screen.width
    height: Screen.height
    color: "blue"
    Bookshelf{
        width: parent.width/4
        height: parent.height
        anchors.right:  homeScreen.right
    }


}
