import QtQuick 2.0
import QtGraphicalEffects 1.0
import './NetLobbyHandler.js' as Handler


Rectangle
{
    id: userListContainer
    color: "gray"

    ListModel
    {
        id: userModel

        ListElement
        {
            userName: "Default Name #42"
        }
    }

    //dynamic user element
    Component
    {
        //holds user data properties
        id: userDelegate

        Column
        {
            spacing: 3
            Rectangle
            {
                id: userBlock
                width: userListContainer.width - scrollbar.width
                height: userListContainer.height / 5.3
                focus: false
                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: "lightgreen" }
                    GradientStop { position: 1.0; color: "darkgreen"  }
                }
                radius: 10
                border.width: 3
                border.color: "green"
                Text
                {
                    id: userBlockText
                    anchors.centerIn: userBlock
                    font.pixelSize: userBlock.height < userBlock.width ? userBlock.width / userName.length : userBlock.height / userName.length
                    color: "gold"
                    text: userName
                }
                opacity: 1.0
            }
        }
    }

    ListView
    {
        id: userView
        model: userModel
        delegate: userDelegate
        anchors.fill: parent
        Rectangle
        {
            id: scrollbar
            anchors.right: parent.right
            y: parent.visibleArea.yPosition * parent.height
            width: 10
            height: parent.visibleArea.heightRatio * parent.height
            color: "black"
            radius: 10
        }
    }

    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {
            userModel.append({"userName": "Darth Vader"});
        }
        else if (event.key == Qt.Key_X)
        {
            userModel.remove({"userName": "Darth Vader"});
        }
    }

}
