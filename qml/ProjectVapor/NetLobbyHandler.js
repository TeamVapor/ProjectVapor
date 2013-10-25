var jacksTag = "DRSANCHEZ: ";
var component;
var object;


//will read computer name later and use as user tag
//e.g. DRSANCHEZ: Some Text
function messageInput()
{
    var messageText = textInput.text.toString();

    if (messageText != "")
    {
        chatText.insert(0, jacksTag.toString());
        chatText.insert(jacksTag.length, messageText.toString());
        chatText.insert(jacksTag.length + messageText.length, "\n");
        textInput.text = "";
    }
}

