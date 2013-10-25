import QtQuick 2.0
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import "./NetLobbyHandler.js" as ChatHandler

ZoomItem
{
    id: chatScreen
    width: 0 //parent.width
    height: 0 //parent.height
    color: "black"

    //sets up the theme of the current system
    SystemPalette { id: activePalette }

    function setDefaultFocus()
    {
        chatTextArea.focus = true;
    }

    //chat area
    Rectangle
    {
        id: chatTextArea
        z: 100
        width: parent.width * 0.75
        height: parent.height * 0.9
        border.width: 4
        border.color: "darkblue"
        anchors.top: parent.top
        focus: true

        KeyNavigation.right: sideBar
        KeyNavigation.down: textInputArea

        TextEdit
        {
            id: chatText
            z: chatTextArea.z + 1
            height: parent.height
            width: parent.width
            color: "black"
            anchors.fill: parent
            activeFocusOnPress: false
            font.pointSize: 16
            textMargin: 7
            wrapMode: TextEdit.Wrap
        }

        Rectangle
        {
            id: textAreaSelected
            width: parent.width
            height: parent.height
            color: "transparent"
            border.width: 6
            border.color: "gold"
            visible: parent.focus
            radius: 8
        }
    }

    //text input
    Rectangle
    {
        id: textInputArea
        width: chatTextArea.width
        height: parent.height - chatTextArea.height
        anchors.top: chatTextArea.bottom
        gradient: Gradient
        {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 1.0; color: "lightgray" }
        }

        border.width: 4
        border.color: "darkblue"

        KeyNavigation.right: buttonArea
        KeyNavigation.up: chatTextArea
        KeyNavigation.down: chatTextArea

        Keys.onReturnPressed: { if (textInputArea.focus) textInput.focus = true; }


        Rectangle
        {
            id: inputAreaSelected
            z: sendButton.z + 5
            width: parent.width
            height: parent.height
            color: "transparent"
            border.width: 6
            border.color: "gold"
            visible: parent.focus
            radius: 8
        }

        TextEdit
        {
            id: textInput
            z: textInputArea.z + 1
            width: parent.width * 0.85
            height: parent.height * 0.9
            color: "black"
            textMargin: 7
            font.pointSize: 16
            wrapMode: TextEdit.Wrap
            focus: true
            Keys.onReturnPressed: ChatHandler.messageInput();

            KeyNavigation.right: sendButton
            KeyNavigation.up: textInputArea

            Rectangle
            {
                id: textInputSelected
                z: 90
                width: parent.width
                height: parent.height
                color: "transparent"
                border.width: 6
                border.color: "gold"
                visible: parent.focus
                radius: 8
            }
        }
        Button
        {
            id: sendButton
            width: parent.width - textInput.width
            height: parent.height
            anchors.left: textInput.right
            border.width: 4
            border.color: "green"
            text: "Send"
            focus: false
            onClicked: ChatHandler.messageInput();

            KeyNavigation.left: textInput
            KeyNavigation.up: textInputArea
            KeyNavigation.right: buttonArea

            Rectangle
            {
                id: sendButtonSelected
                z: 90
                width: parent.width
                height: parent.height
                color: "transparent"
                border.width: 6
                border.color: "gold"
                visible: parent.focus
                radius: 8
            }
        }
    }


    //sidebar
    Rectangle
    {
        id: sideBar
        width: chatScreen.width * 0.25
        height: chatScreen.height
        anchors.right: chatScreen.right
        color: "black"
        border.width: 4
        border.color: "darkblue"

        KeyNavigation.left: chatTextArea
        KeyNavigation.right: chatTextArea
        KeyNavigation.down: buttonArea

        Keys.onReturnPressed: { if (sideBar.focus) userList.focus = true; }

        Rectangle
        {
            id: sideBarSelected
            width: parent.width
            z: 90
            height: parent.height
            color: "transparent"
            border.width: 6
            border.color: "gold"
            visible: parent.focus
            radius: 8
        }

        UserList
        {
            id: userList
            anchors.top: sideBar.top
            height: sideBar.height * 0.4
            width: sideBar.width
            focus: false

            KeyNavigation.up: sideBar
            KeyNavigation.down: lobbyList
            KeyNavigation.left: chatTextArea
            KeyNavigation.right: chatTextArea

            Rectangle
            {
                id: userListSelected
                z: 90
                width: parent.width
                height: parent.height
                color: "transparent"
                border.width: 6
                border.color: "gold"
                visible: parent.focus
                radius: 8
            }
        }

            //need to create lobby object and its model container
        LobbyList
        {
            id: lobbyList
            anchors.top: userList.bottom
            height: parent.height * 0.4
            width: parent.width
            focus: false

            KeyNavigation.up: userList
            KeyNavigation.left: chatTextArea
            KeyNavigation.right: chatTextArea
            KeyNavigation.down: buttonArea

            Keys.onBackPressed: { sideBar.focus = true; }

            Rectangle
            {
                id: lobbyListSelected
                z: 90
                width: parent.width
                height: parent.height
                color: "transparent"
                border.width: 6
                border.color: "gold"
                visible: parent.focus
                radius: 8
            }
        }


        //button navigation grid
        Rectangle
        {
            id: buttonArea
            width: sideBar.width
            height: sideBar.height * 0.2
            anchors.top: lobbyList.bottom
            focus: false
            property bool backButtonPressed: false

            Rectangle
            {
                id: buttonAreaSelected
                z: 90
                width: parent.width
                height: parent.height
                color: "transparent"
                border.width: 6
                border.color: "gold"
                visible: parent.focus
                radius: 8
            }

            Keys.onReturnPressed: { if (buttonArea.focus) playButton.focus = true; }

            Button
            {
                id: playButton
                width: parent.width
                height: parent.height / 2
                anchors.top: buttonArea.top
                text: "Play Game"
                border.width: 4
                border.color: "green"
                onClicked:
                {
                    buttonArea.backButtonPressed = false;
                    chatScreen.visible = false;
                    zoomsurface.zoomOut.start();
                }
                focus: false

                KeyNavigation.down: backButton

                Rectangle
                {
                    id: playButtonSelected
                    z: 90
                    width: parent.width
                    height: parent.height
                    color: "transparent"
                    border.width: 6
                    border.color: "gold"
                    visible: parent.focus
                    radius: 8
                }
            }

            Button
            {
                id: backButton
                width: parent.width
                height: parent.height / 2
                anchors.top: playButton.bottom
                text: "Back Home"
                border.width: 4
                border.color: "red"
                onClicked:
                {
                    buttonArea.backButtonPressed = true;
                    chatScreen.visible = false;
                    zoomsurface.zoomOut.start();
                    /*zoomsurface.scale = zoomsurface.scaledZoomValue;
                    zoomsurface.x = 0;
                    zoomsurface.y = 0;*/
                    router.focus = true;
                }
                focus: false

                KeyNavigation.up: playButton

                Rectangle
                {
                    id: backButtonSelected
                    z: 90
                    width: parent.width
                    height: parent.height
                    color: "transparent"
                    border.width: 6
                    border.color: "gold"
                    visible: parent.focus
                    radius: 8
                }
            }
        }
    }
    onZoomedOutStopped: function()
    {
        if (buttonArea.backButtonPressed)
        {
            monitor.focus = true;
        }
        else
        {
            zoomsurface.zoomToItemTopRight(bookshelf);
            bookshelf.focus = true;
        }
    }
}
