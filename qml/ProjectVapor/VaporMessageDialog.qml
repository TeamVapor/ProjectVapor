import QtQuick 2.0
import QtQuick.Window 2.1


//on use, set dialog message
//then call show and pass the previous focus as parameter

ZoomItem
{
    id: vaporDialogContainer
    width: 0
    height: 0
    z: 90000
    visible: true
    focus: false
    color: "transparent"
    scalable: false
    pressable: false

    property var lastFocus: null
    property string dialogMessage: "Default test message."

    VaporRectangle
    {
        id: vaporDialog
        width: parent.width
        height: parent.height
        color: base
        z: vaporDialogContainer.z + 90000
        opacity: 1
        focus: false

        border.width: 10
        border.color: shadow

        TextEdit
        {
            id: messageText
            height: parent.height * 0.6
            width: parent.width
            color: light
            text: dialogMessage
            font.pointSize: 16
            wrapMode: Text.Wrap
            textMargin: 50
            activeFocusOnPress: false
        }


        Row
        {
            id: buttonRowContainer
            width: parent.width / 2
            height: parent.height * 0.25
            anchors.top: messageText.bottom
            anchors.right: parent.right
            visible: true
            spacing: 15

            Button
            {
                id: acceptButton
                width: (parent.width / 2) * 0.85
                height: parent.height * 0.85
                focus: false
                text: "Accept"

                KeyNavigation.left: cancelButton
                KeyNavigation.right: cancelButton

                Keys.onReturnPressed: vaporDialogContainer.hide()
            }

            Button
            {
                id: cancelButton
                width: (parent.width / 2) * 0.85
                height: parent.height * 0.85
                focus: false
                text: "Cancel"

                KeyNavigation.left: acceptButton
                KeyNavigation.right: acceptButton

                Keys.onReturnPressed: vaporDialogContainer.hide()
            }
        }
    }

    function setDialogMessage (message)
    {
        dialogMessage = message;
    }

    function setDefaultFocus ()
    {
        acceptButton.focus = true;
    }

    function show (parent)
    {
        visible = true;
        lastFocus = parent;
        setDefaultFocus();
    }

    function hide ()
    {
        visible = false;
        focus = false;
        lastFocus.focus = true;
    }
}

