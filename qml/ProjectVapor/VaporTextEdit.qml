import QtQuick 2.0
import './ChatHandler.js' as Handler


VaporRectangle
{
    id: textInputContainer
    width: parent.width * 0.5
    height: parent.height * 0.2
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    color: "transparent"
    pressable: false

    //KeyNavigation.up: textAreaContainer
    //KeyNavigation.left: lobbyList

    Keys.onReturnPressed:
    {
        textInputContainer.focus = false;
        inputContainer.focus = true;
        event.accepted = true;
    }

    function setDefaultFocus()
    {
        inputContainer.focus = true;
    }

    //begin text input bar
    VaporRectangle
    {
        id: inputContainerPositioner
        width: parent.width * 0.8
        height: parent.height
        anchors.left: parent.left
        color: "transparent"

        //begin text input bar
        //need to modularize for keyboard input
        VaporRectangle
        {
            id: inputContainer
            width: parent.width * 0.95
            height: parent.height * 0.95
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: dark
            focus: false

            Keys.onReturnPressed:
            {
                inputContainer.focus = false;
                textInput.focus = true;
                event.accepted = true;
            }

            KeyNavigation.right: sendButton
         //   KeyNavigation.up: textAreaContainer

            TextEdit
            {
                id: textInput
                width: parent.width
                height: parent.height
                textMargin: 8
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                color: light
                font.pointSize: 16
                activeFocusOnPress: true
                wrapMode: TextEdit.Wrap
                focus: false

                Keys.onReturnPressed:
                {
                    sipKeyboard.setInput(textInput);
                    sipKeyboard.visible = true;
                    sipKeyboard.focus = true;
                }

                Keys.onEscapePressed:
                {
                    textInput.focus = false;
                    inputContainer.focus = true;
                    event.accepted = true;
                }

                //on pressed, open onscreenkeyboard
            }
        }
    }//end text input bar

    //begin send button
    VaporRectangle
    {
        id: sendButtonPositioner
        width: parent.width * 0.2
        height: parent.height
        anchors.right: parent.right
        color: "transparent"
        pressable: false

        Button
        {
            id: sendButton
            width: parent.width * 0.95
            height: parent.height * 0.95
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Send"
            KeyNavigation.left: inputContainer
         //   KeyNavigation.up: textAreaContainer

            onClicked: Handler.messageInput();
        }
    }//end send button

}
