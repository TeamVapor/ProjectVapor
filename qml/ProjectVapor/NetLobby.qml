import QtQuick 2.0
import './ChatHandler.js' as Handler

VaporRectangle
{
    id: netLobbyContainer
    width: 1920 //width: 0 //parent.width
    height: 1080 //height: 0 //parent.height
    visible: false
    focus: false
    z: parent.z + 1
    color: base
    objectName: "NetLobby"
    property string lobbyName: ""
    // message recieved from message system
    function submitMessage(message)
    {
        textContainer.text += (message + '\n');
    }


    function setDefaultFocus()
    {
        userListContainer.focus = true;
    }

    //begin user list area
    VaporRectangle
    {
        id: userListContainer
        width: parent.width * 0.25
        height: parent.height * 0.5
        anchors.left: parent.left
        anchors.top: parent.top
        color: "transparent"

        KeyNavigation.up: lobbyListContainer
        KeyNavigation.down: lobbyListContainer
        KeyNavigation.right: textAreaContainer
        KeyNavigation.left: settingsButtons

        UserList
        {
            id: userList
            width: parent.width * 0.95
            height: parent.height * 0.95
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }//end user list area

    //begin lobby list area
    VaporRectangle
    {
        id: lobbyListContainer
        width: parent.width * 0.25
        height: parent.height * 0.5
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        color: "transparent"

        KeyNavigation.up: userListContainer
        KeyNavigation.down: userListContainer
        KeyNavigation.right: textEditor
        KeyNavigation.left: backButton

        Keys.onReturnPressed:
        {
            gameLobby.visible = true;
            lobbyListContainer.focus = false;
            netLobby.visible = false;
            gameLobby.setDefaultFocus();
            gameLobby.anchors.centerIn = netLobby;
            zoomsurface.targetItem = gameLobby;
        }

        LobbyList
        {
            id: lobbyList
            width: parent.width * 0.95
            height: parent.height * 0.95
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }//end lobby list area

    //begin text area
    VaporRectangle
    {
        id: textAreaContainer
        width: parent.width * 0.5
        height: parent.height * 0.8
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"
        pressable: false

        //perhaps allow selection later for text grabbing, etc.. from group chat?

        KeyNavigation.up: textEditor
        KeyNavigation.down: textEditor
        KeyNavigation.left: userListContainer
        KeyNavigation.right: settingsButtons

        VaporRectangle
        {
            id: textArea
            width: parent.width * 0.95
            height: parent.height * 0.95
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: dark

            TextEdit
            {
                id: textContainer
                width: parent.width
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: light
                textMargin: 8
                font.pointSize: 16
                wrapMode: TextEdit.Wrap
                activeFocusOnPress: false
            }
        }
    }//end text area

    VaporTextEdit
    {
        id: textEditor
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    //begin settings area
    VaporRectangle
    {
        id: settingsAreaContainer
        width: parent.width * 0.25
        height: parent.height * 0.15
        anchors.top: parent.top
        anchors.right: parent.right
        pressable: false
        color: "transparent"

        VaporRectangle
        {
            id: settingsButtons
            width: parent.width * 0.95
            height: parent.height * 0.5
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: base
            pressable: false

            KeyNavigation.left: textAreaContainer
            KeyNavigation.right: userListContainer

            Keys.onReturnPressed:
            {
                settingsButtons.focus = false;
                fontButton.focus = true;
                event.accepted = true;
            }

            //place holder buttons
            Button
            {
                id: fontButton
                width: parent.width * 0.2
                height: parent.height
                anchors.left: parent.left
                text: "Font"
                KeyNavigation.right: sizeButton
                KeyNavigation.left: clearChatButton
                KeyNavigation.up: backButton
                KeyNavigation.down: playButton
            }
            Button
            {
                id: sizeButton
                width: parent.width * 0.2
                height: parent.height
                anchors.left: fontButton.right
                text: "Size"
                KeyNavigation.right: fontColorButton
                KeyNavigation.left: fontButton
                KeyNavigation.up: backButton
                KeyNavigation.down: playButton
            }
            Button
            {
                id: fontColorButton
                width: parent.width * 0.2
                height: parent.height
                anchors.left: sizeButton.right
                text: "Color"
                KeyNavigation.right: setUserNameButton
                KeyNavigation.left: sizeButton
                KeyNavigation.up: backButton
                KeyNavigation.down: playButton
            }
            Button
            {
                id: setUserNameButton
                width: parent.width * 0.2
                height: parent.height
                anchors.left: fontColorButton.right
                text: "UserName"
                KeyNavigation.right: clearChatButton
                KeyNavigation.left: fontColorButton
                KeyNavigation.up: backButton
                KeyNavigation.down: playButton
            }
            Button
            {
                id: clearChatButton
                width: parent.width * 0.2
                height: parent.height
                anchors.left: setUserNameButton.right
                text: "ClearChat"
                KeyNavigation.right: fontButton
                KeyNavigation.left: setUserNameButton
                KeyNavigation.up: backButton
                KeyNavigation.down: playButton
            }
            //end place holder buttons
        }
    }//end settings area

    //need to define something for file share
    //between the top buttons and bottom buttons

    //application navigation buttons
    VaporRectangle
    {
        id: navigationButtonContainer
        width: parent.width * 0.25
        height: parent.height * 0.35
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        color: "transparent"
        pressable: false
        property bool backButtonPressed: false

        VaporRectangle
        {
            id: playContainer
            width: parent.width
            height: parent.height * 0.5
            color: "transparent"
            anchors.top: parent.top
            pressable: false

            Button
            {
                id: playButton
                width: parent.width * 0.95
                height: parent.height * 0.95
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Start Lobby"

                //need to reset these once center piece of
                //right hand screen is determined
                KeyNavigation.up: settingsButtons
                KeyNavigation.down: backButton
                KeyNavigation.left: textEditor
                KeyNavigation.right: lobbyListContainer

                onClicked:
                {
                    navigationButtonContainer.backButtonPressed = false;
                    netLobbyContainer.visible = false;
                    zoomsurface.zoomOutToFull();
                    vaporInputDialog.setDialogMessage("Please enter a lobby name.");
                    vaporInputDialog.show(bookshelf, lobbyName);
                    //working on interfacing input dialog to return userdata
                    vaporInputDialog.accepted.connect(openGameLobby);
                }

            }
        }

        VaporRectangle
        {
            id: backContainer
            width: parent.width
            height: parent.height * 0.5
            color: "transparent"
            anchors.bottom: parent.bottom
            pressable: false

            Button
            {
                id: backButton
                width: parent.width * 0.95
                height: parent.height * 0.95
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Back Home"

                //need to reset these once center piece of
                //right hand screen is determined
                KeyNavigation.up: playButton
                KeyNavigation.down: settingsButtons
                KeyNavigation.left: textEditor
                KeyNavigation.right: lobbyListContainer

                onClicked:
                {
                    navigationButtonContainer.backButtonPressed = true;
                    netLobbyContainer.visible = false;
                    zoomsurface.zoomOutToFull();
                    router.focus = true;
                }
            }
        }
    }//end application navigation buttons

    onZoomedOutStopped: function()
    {
        if (navigationButtonContainer.backButtonPressed)
        {
            router.focus = true;
        }
        else
        {
            zoomsurface.zoomToItemTopRight(bookshelf);
            //bookshelf.focus = true;
        }
    }


    function openGameLobby()
    {
        NSDServices.startGameLobby(lobbyName);
    }

}
