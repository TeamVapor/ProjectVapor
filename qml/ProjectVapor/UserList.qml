import QtQuick 2.0
import QtGraphicalEffects 1.0


VaporRectangle
{
    id: userListContainer
    color: alternateBase
    focus: false
    pressable: false

    //dynamic user element
    Component
    {
        //holds user data properties
        id: userDelegate

        Column
        {
            spacing: 3
            VaporRectangle
            {
                id: userBlock
                width: userListContainer.width - scrollbar.width
                height: userListContainer.height / 5.3
                focus: false
                gradient: Gradient
                {
                    GradientStop { position: 0.00; color: "#394053"; }
                    GradientStop { position: 1.00; color: "#3a4858"; }
                }
                border.width: 3
                border.color: "#b3ccee"
                Text
                {
                    id: userBlockText
                    property string userName: NSDUserList[index]
                    anchors.centerIn: userBlock
                    font.pixelSize: userBlock.height < userBlock.width ? userBlock.width / userName.length : userBlock.height / userName.length
                    color: "black"
                    text: userName
                }
                opacity: 1.0
            }
        }
    }

    ListView
    {
        id: userView
        model: NSDUserList ? NSDUserList:0
        delegate: userDelegate
        anchors.fill: parent
        focus: false

        Rectangle
        {
            id: scrollbar
            anchors.right: parent.right
            y: parent.visibleArea.yPosition * parent.height
            width: 10
            height: parent.visibleArea.heightRatio * parent.height
            color: "#2b3c58"
        }

        header: VaporRectangle
        {
            id: headerBlock
            width: userListContainer.width - scrollbar.width
            height: userListContainer.height / 8
            focus: false
            gradient: Gradient
            {
                GradientStop { position: 0.00; color: light; }
                GradientStop { position: 1.00; color: dark; }
            }
            border.width: 3
            border.color: shadow
            Text
            {
                id: headerBlockText
                anchors.centerIn: headerBlock
                font.pixelSize: headerBlock.height < headerBlock.width ? headerBlock.width / text.length : headerBlock.height / text.length
                color: text
                text: "User List"
            }
        }
    }
}
