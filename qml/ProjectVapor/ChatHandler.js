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
        textContainer.insert(0, jacksTag.toString());
        textContainer.insert(jacksTag.length, messageText.toString());
        textContainer.insert(jacksTag.length + messageText.length, "\n");
        textInput.text = "";
    }
}

