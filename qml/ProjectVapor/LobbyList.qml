import QtQuick 2.0

VaporRectangle
{
    id: lobbyListContainer
    color: alternateBase
    focus: false
    pressable: false


    /**************************************************************************
    *
    * this object describes how to format and display data
    * collected from the model used by the ListView
    *
    *
    *
    ***************************************************************************/
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

    /**************************************************************************
    *
    * this object manages the delegate and model of the lobby list
    * contains scrollbar
    *
    *
    *
    ***************************************************************************/
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

        header: VaporRectangle
        {
            id: headerBlock
            width: lobbyListContainer.width - scrollbar.width
            height: lobbyListContainer.height / 8
            focus: false
            gradient: Gradient
            {
                GradientStop { position: 0.00; color: light; }
                GradientStop { position: 1.00; color: dark; }
            }
            border.width: 3
            border.color: shadow
            Text
            {
                id: headerBlockText
                anchors.centerIn: headerBlock
                font.pixelSize: headerBlock.height < headerBlock.width ? headerBlock.width / text.length : headerBlock.height / text.length
                color: text
                text: "Lobby List"
            }
        }
    }

    function addLobby(name)
    {
        lobbyList.model.append(name);
    }
}
