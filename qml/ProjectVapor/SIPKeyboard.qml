import QtQuick 2.0

FocusScope
{
    property var currentFocus: null
    property alias inputtext: textField.text

    //used to return to previous selection
    property var lastParent: null

    Rectangle {
        id: keyboardMain
        width: ScreenWidth
        height: ScreenHeight
        x:0
        y:0
        color: "black"
        opacity: .85
        property int keyState: 0
        property int pathMargin: 50
        focus:true
        SIPCharPanel
        {
            id:leftPanel
            width: ScreenWidth/4
            height:ScreenHeight/4
            anchors.verticalCenter: keyboardMain.verticalCenter
            anchors.left: keyboardMain.left
            anchors.leftMargin: keyboardMain.pathMargin
            leftB: "E"
            leftA: "G"
            upB: "A"
            upA: "C"
            downB:"B"
            downA:"D"
            rightB:"F"
            rightA:"H"
        }
        SIPCharPanel
        {
            id:rightPanel
            width: ScreenWidth/4
            height:ScreenHeight/4
            anchors.verticalCenter: keyboardMain.verticalCenter
            anchors.right: keyboardMain.right
            anchors.rightMargin: keyboardMain.pathMargin
            leftB: "M"
            leftA: "O"
            upB: "I"
            upA: "K"
            downB:"J"
            downA:"L"
            rightB:"N"
            rightA:"P"
        }
        SIPCharPanel
        {
            id:upPanel
            width: ScreenWidth/4
            height:ScreenHeight/4
            anchors.top: keyboardMain.top
            anchors.topMargin: keyboardMain.pathMargin
            anchors.horizontalCenter: keyboardMain.horizontalCenter
            leftB: "U"
            leftA: "W"
            upB: "Q"
            upA: "S"
            downB:"R"
            downA:"T"
            rightB:"V"
            rightA:"X"
        }
        SIPCharPanel
        {
            id:downPanel
            width: ScreenWidth/4
            height:ScreenHeight/4
            anchors.bottom: keyboardMain.bottom
            anchors.bottomMargin: keyboardMain.pathMargin
            anchors.horizontalCenter: keyboardMain.horizontalCenter
            downB:"Y"
            downA:"Z"
            rightB:"<"
            rightA:">"
            Component.onCompleted:
            {
                leftChoice.aBorder.visible= false;
                leftChoice.bBorder.visible= false;
                upChoice.aBorder.visible= false;
                upChoice.bBorder.visible= false;
            }
        }
        Rectangle
        {
            id: textInputbGround
            color: "lightsteelblue"
            width: (ScreenWidth - (rightPanel.width * 2 + keyboardMain.pathMargin*2))
            height: (ScreenHeight/6)
            border.color: "gray"
            border.width: 2
            radius: 12
            anchors.centerIn: keyboardMain
            clip: true
            TextInput
            {
                id: textField
                z: keyboardMain.z +1
                width:parent.width *.9
                height: parent.height *.9
                visible: true
                text:""
                color:"black"
                font.pixelSize: height *.8
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        //0 = beginning state
        //1 = up state 1
        //2 = left state 1
        //3 = right state 1
        //4 = down state 1
        //5 = up->up state 2
        //6 = up->left state 2
        //7 = up->right state 2
        //8 = up->down state 2
        //9 = left->up state 2
        //10 = left->left state 2
        //11 = left->right state 2
        //12 = left->down state 2
        //13 = right->up state 2
        //14 = right->left state 2
        //15 = right->right state 2
        //16 = right->down state 2
        //17 = down->up state 2
        //18 = down->left state 2
        //19 = down->right state 2
        //20 = down->down state 2
        Keys.onLeftPressed:
        {
            if(keyState > 0) // if not at first step
            {
                if(keyState === 1)
                {
                    keyState = 6; // up->left
                    upPanel.leftChoice.focus = true;
                }
                else if(keyState === 2)
                {
                    keyState = 10; // left->left
                    leftPanel.leftChoice.focus = true;
                }
                else if(keyState === 3)
                {
                    keyState = 14; // right->left
                    rightPanel.leftChoice.focus = true;
                }
                else if(keyState === 4)
                {
                    keyState = 18; // down->left
                    downPanel.leftChoice.focus = true;
                }
                else
                {
                    keyState =2; // select left panel
                    leftPanel.focus = true;
                }
            }
            else
            {
                keyState = 2; // select left panel
                leftPanel.focus = true;
            }
            //console.log("state " + keyState);
        }
        Keys.onRightPressed:
        {
            if(keyState > 0) // if not at first step
            {
                if(keyState === 1)
                {
                    keyState = 7; // up->right
                    upPanel.rightChoice.focus = true;
                }
                else if(keyState === 2)
                {
                    keyState = 11; // left->right
                    leftPanel.rightChoice.focus = true;
                }
                else if(keyState === 3)
                {
                    keyState = 15; // right->right
                    rightPanel.rightChoice.focus = true;
                }
                else if(keyState === 4)
                {
                    keyState = 19; // down->right
                    downPanel.rightChoice.focus = true;
                }
                else
                {
                    keyState = 3; // select right panel
                    rightPanel.focus = true;
                }
            }
            else
            {
                keyState = 3; // select right panel
                rightPanel.focus = true;
            }
           // console.log("state " + keyState);
        }
        Keys.onUpPressed:
        {
            if(keyState > 0) // if not at first step
            {
                    if(keyState === 1)
                    {
                        keyState = 5; // up->up
                        upPanel.upChoice.focus = true;
                    }
                    else if(keyState === 2)
                    {
                        keyState = 9; // left->up
                        leftPanel.upChoice.focus = true;
                    }
                    else if(keyState === 3)
                    {
                        keyState = 13; // right->up
                        rightPanel.upChoice.focus = true;
                    }
                    else if(keyState === 4)
                    {
                        keyState = 17; // down->up
                        downPanel.upChoice.focus = true;
                    }
                    else
                    {
                        keyState = 1; // select up panel
                        upPanel.focus = true;
                    }
            }
            else
            {
                keyState = 1; // select up panel
                upPanel.focus = true;
            }
            //console.log("state " + keyState);
        }

        Keys.onDownPressed:
        {

            if(keyState > 0) // if not at first step
            {
                if(keyState === 1)
                {
                    keyState = 8; // up->down
                    upPanel.downChoice.focus = true;
                }
                else if(keyState === 2)
                {
                    keyState = 12; // left->down
                    leftPanel.downChoice.focus = true;
                }
                else if(keyState === 3)
                {
                    keyState = 16; // right->down
                    rightPanel.downChoice.focus = true;
                }
                else if(keyState === 4)
                {
                    keyState = 20; // down->down
                    downPanel.downChoice.focus = true;
                }
                else
                {
                    keyState = 4; // select down panel
                    downPanel.focus = true;
                }
            }
            else
            {
                keyState = 4; // select down panel
                downPanel.focus = true;
            }

           // console.log("state " + keyState);
       }
       Keys.onPressed:
       {
           if(event.nativeScanCode == 14)
           {
               sipKeyboard.visible = false;
               sipKeyboard.currentFocus.focus = true;
           }
           else if (event.key == Qt.Key_Escape)
           {
               sipKeyboard.visible = false;
               sipKeyboard.focus = false;
               lastParent.focus = true;
           }
       }
    }
    function setInput(input)
    {
        textField.text = input.text;
        currentFocus = input;
        lastParent = input.parent;
    }
}
