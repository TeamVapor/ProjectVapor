//will read computer name later and use as user tag
//e.g. DRSANCHEZ: Some Text
function messageInput( username, message, container)
{
    if (message !== "")
    {
        container.text += username.toString() +': ';
        container.text += message;
        //container.insert(username.length + message.length, "\n");
    }
}

