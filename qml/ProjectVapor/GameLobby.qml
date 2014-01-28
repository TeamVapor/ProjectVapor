import QtQuick 2.0
import './ChatHandler.js' as Handler

VaporRectangle
{
    id: gameLobbyContainer
    width: 1920 //width: 0 //parent.width
    height: 1080 //height: 0 //parent.height
    visible: false
    focus: false
    z: parent.z + 1
    color: base

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
        KeyNavigation.left: vaporVideo

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

        LobbyList
        {
            id: lobbyList
            width: parent.width * 0.95
            height: parent.height * 0.95
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }//end lobby list area

    //begin game banner area
    VaporRectangle
    {
        id: gameBannerContainer
        width: parent.width * 0.5
        height: parent.height * 0.2
        color: "transparent"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        pressable: false

        VaporRectangle
        {
            id: gameBanner
            width: parent.width * 0.95
            height: parent.height * 0.95
            color: shadow
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            KeyNavigation.left: userListContainer
            KeyNavigation.down: textAreaContainer
            KeyNavigation.up: textEditor
            KeyNavigation.right: vaporVideo

            Image
            {
                id: bannerImage
                width: parent.width
                height: parent.height
                fillMode: Image.PreserveAspectFit
                source: VaporArcade.getCoverDirectory() +"/tmnt4_banner.png"
            }
        }
    }//end game banner area

    //begin text area
    VaporRectangle
    {
        id: textAreaContainer
        width: parent.width * 0.5
        height: parent.height * 0.6
        anchors.bottom: textEditor.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"
        pressable: false

        //perhaps allow selection later for text grabbing, etc.. from group chat?

        KeyNavigation.up: gameBanner
        KeyNavigation.down: textEditor
        KeyNavigation.left: userListContainer
        KeyNavigation.right: vaporVideo

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

    VaporRectangle
    {
        id: videoContainer
        width: parent.width * 0.25
        height: parent.height * 0.45
        anchors.top: parent.top
        anchors.right: parent.right
        color: "transparent"
        pressable: false

        VaporVideoPlayer
        {
            id: vaporVideo
            width: parent.width * 0.95
            height: parent.height * 0.95
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"
            KeyNavigation.left: gameBanner
            KeyNavigation.right: userListContainer
            KeyNavigation.up: backButton
            KeyNavigation.down: playButton

            Keys.onReturnPressed:
            {
                vaporVideo.source = vaporVideo.swapSource();
                event.accepted = true;
            }
        }
    }

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
                text: "Start Game"

                //need to reset these once center piece of
                //right hand screen is determined
                KeyNavigation.up: vaporVideo
                KeyNavigation.down: backButton
                KeyNavigation.left: textEditor
                KeyNavigation.right: lobbyListContainer

                onClicked:
                {
                    //start selected game
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

                KeyNavigation.up: playButton
                KeyNavigation.down: vaporVideo
                KeyNavigation.left: textEditor
                KeyNavigation.right: lobbyListContainer

                onClicked:
                {
                    navigationButtonContainer.backButtonPressed = true;
                    gameLobbyContainer.visible = false;
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
            //start game animation
        }
    }
}
