import QtQuick 2.0
import QtMultimedia 5.0

VaporRectangle
{
    id: videoContainer

    property alias source: player.source

    MediaPlayer
    {
        id: player
        source: "../../turtles1.webm"
        muted: true
        autoPlay: true
        property bool trailerPicker: false

        onStopped: { player.source = swapSource(); }
    }

    VideoOutput
    {
        id: videoOutput
        source: player
        anchors.fill: parent
    }

    //needs to be modularized for dynamic source selection
    function swapSource()
    {
        if (player.trailerPicker)
        {//trailerPicker == true
            player.trailerPicker = false;
            return "../../turtles1.webm";
        }
        else if (!player.trailerPicker)
        {//trailerPicker == false
            player.trailerPicker = true;
            return "../../turtles2.webm";
        }
    }
}
