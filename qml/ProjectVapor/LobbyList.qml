import QtQuick 2.0

Rectangle
{
    id: lobbyListContainer

    //define open lobby list container look
    color: "gray"

    ListModel
    {
        id: lobbyListModel

        ListElement
        {
            lobbyName: "LobbyName"
        }
    }

    Component
    {
        id: lobbyDelegate

        Column
        {
            spacing: 3
            Rectangle
            {
                id: lobbyBlock
                width: lobbyListContainer.width
                height: lobbyListContainer.height / 5.3
                focus: false
                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: "blue" }
                    GradientStop { position: 1.0; color: "darkblue" }
                }
                radius: 10
                border.width: 3
                border.color: "blue"
                Text
                {
                    id: lobbyBlockText
                    anchors.centerIn: lobbyBlock
                    font.pixelSize: lobbyBlock.height < lobbyBlock.width ? lobbyBlock.width / lobbyName.length : lobbyBlock.height / lobbyName.length
                    color: "gold"
                    text: lobbyName
                }
            }
        }
    }

    ListView
    {
        id: lobbyList
        model: lobbyListModel
        delegate: lobbyDelegate
        anchors.fill: parent
        clip: true

        Rectangle
        {
            id: scrollbar
            anchors.right: parent.right
            y: parent.visibleArea.yPosition * parent.height
            width: 10
            height: parent.visibleArea.heightRatio * parent.height
            color: "black"
            radius: 10
        }
    }

    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
            lobbyListModel.append({"lobbyName": "TeamVapor Lobby"});
        else if (event.key == Qt.Key_X)
            lobbyListModel.remove({"lobbyName": "TeamVapor Lobby"});
    }
}
