import QtQuick 2.0

VaporRectangle
{
    id: lobbyListContainer
    color: alternateBase
    focus: false
    pressable: false

/*
    //defines the data within the list
    ListModel
    {
        id: lobbyListModel

        ListElement
        {
            lobbyName: "LobbyName"
        }
    }*/


    //defines how the data from list model
    //is displayed from the list view
    Component
    {
        id: lobbyDelegate

        Column
        {
            spacing: 3
            VaporRectangle
            {
                id: lobbyBlock
                width: lobbyListContainer.width - scrollbar.width
                height: lobbyListContainer.height / 5.3
                focus: false
                gradient: Gradient
                {
                    GradientStop { position: 0.00; color: "#394053"; }
                    GradientStop { position: 1.00; color: lobbyBlock.dark; }
                }
                border.width: 3
                border.color: lobbyBlock.light
                Text
                {
                    id: lobbyBlockText
                    property string lobbyName: NSDGameLobbyList[index]
                    anchors.centerIn: lobbyBlock
                    font.pixelSize: lobbyBlock.height < lobbyBlock.width ? lobbyBlock.width / lobbyName.length : lobbyBlock.height / lobbyName.length
                    color: "black"
                    text: lobbyName
                }
            }
        }
    }

    //manages the list model and delegate
    //as well as contains its scrollbar
    ListView
    {
        id: lobbyList
        model: NSDGameLobbyList
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
            color: "#2b3c58"
            clip: true
        }
    }

    /*Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
            lobbyListModel.append({"lobbyName": "TeamVapor Lobby"});
        else if (event.key == Qt.Key_X)
            lobbyListModel.remove({"lobbyName": "TeamVapor Lobby"});
    }*/
}
