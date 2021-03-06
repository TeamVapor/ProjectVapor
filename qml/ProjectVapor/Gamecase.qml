import QtQuick 2.0

Component{
    id : wrapper
    VaporRectangle{
        property alias text: displayText
        id: gameCase
        color: "blue"
        border.color: "black"
        border.width: 2
        height: shelfGrid.cellHeight *.92
        width: shelfGrid.cellWidth *.98
        Text
        {
            id: displayText
            visible: true
            text: display
            color: "yellow"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: width*.8
        }
        Image
        {
            id: displayImage
            visible: false
            anchors.fill: parent
            fillMode: Image.Stretch
        }
        Component.onCompleted:
        {
            if(isGame)
            {
                displayText.visible = false;
                if(display != "")
                {
                    displayImage.source = VaporArcade.getCoverDirectory() + display;
                    displayImage.visible = true;
                    gameCase.visible = true;
                    validIndexArray[validIndexArray.length] = index;
                }
                else
                {
                    displayImage.visible = false;
                    gameCase.visible = false;
                }
            }
            else
            {
                displayText.text = display;
                //  console.log("adding" +index);
                validIndexArray[validIndexArray.length] = index;
            }
        }
	Keys.onPressed:
	{
		if(event.key == Qt.Key_Return)
			start();
	}
        property var start: function()
        {
            if(isGame && display != "")
            {
                console.log(VaporArcade.AppSettings.InterfacesDirectory);
            }
        }
    }
}
