import QtQuick 2.0
import QtQuick.Window 2.1

//on use, set dialog message
//then call show and pass the previous focus as parameter

VaporRectangle
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

    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter

    signal accepted

    property var curParent: null
    property string dialogMessage: "Enter a username."
    property alias userInput: inputBox.inputText

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

        VaporRectangle
        {
            id: messageContainer
            width: vaporDialog.width * 0.9
            height: vaporDialog.height * 0.4
            color: "transparent"

            TextEdit
            {
                id: messageText
                height: parent.height
                width: parent.width
                color: light
                text: dialogMessage
                font.pointSize: 16
                wrapMode: Text.Wrap
                textMargin: 50
                activeFocusOnPress: false
            }
        }

        VaporTextEdit
        {
            id: inputBox
            width: vaporDialog.width
            height: messageContainer.height
            anchors.top: messageContainer.bottom
            anchors.horizontalCenter: vaporDialog.horizontalCenter
            button.text: "OK"
            scalable: false

            button.onClicked:
            {
                vaporDialogContainer.hide();
                inputBox.text = ""
            }
        }
    }

  /*  //use x,y to position dialog
    function centerIn (parent)
    {

    }
*/
    function getUserInput ()
    {
        return userInput;
    }

    function setDialogMessage (message)
    {
        dialogMessage = message;
    }

    function setDefaultFocus ()
    {
        inputBox.focus = true;
    }

    function show (parent)
    {
        visible = true;
        curParent = parent;
        setDefaultFocus();
    }

    function hide ()
    {
        visible = false;
        focus = false;
        curParent.focus = true;
        zoomsurface.zoomOutToFull();
        userInput = inputBox.readInputText();
        inputBox.clearInputText();
        accepted();
    }
}

