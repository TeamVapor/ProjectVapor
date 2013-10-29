import QtQuick 2.0
import QtGraphicalEffects 1.0
Rectangle
{
    id: panelMain
    width:ScreenWidth/4
    height: width
    border.color: "lightsteelblue"
    radius: 12
    color: panelMain.focus ? "yellow":"white"
    property alias leftB: leftChoice.bText
    property alias leftA: leftChoice.aText
    property alias upB: upChoice.bText
    property alias upA: upChoice.aText
    property alias rightB: rightChoice.bText
    property alias rightA: rightChoice.aText
    property alias downB: downChoice.bText
    property alias downA: downChoice.aText
    property alias rightChoice: rightChoice
    property alias leftChoice: leftChoice
    property alias upChoice: upChoice
    property alias downChoice: downChoice
    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "#000222";
        }
        GradientStop {
            position: 1.00;
            color: "#0010fd";
        }
    }
   SIPButtonChoice
   {
      id:leftChoice
      anchors.left: parent.left
      anchors.verticalCenter: parent.verticalCenter
      anchors.leftMargin: 8
   }
   SIPButtonChoice
   {
       id: rightChoice
       anchors.right: parent.right
       anchors.verticalCenter: parent.verticalCenter
       anchors.rightMargin: 8
   }
   SIPButtonChoice
   {
      id:upChoice
      anchors.top: parent.top
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.topMargin: 8
   }
   SIPButtonChoice
   {
       id:downChoice
       anchors.bottom: parent.bottom
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.bottomMargin: 8
    }
   Glow
   {
       anchors.centerIn: panelMain
       color: "yellow"
       width: dpad.width *1.05
       height: dpad.height *1.05
       source:dpad
       samples:16
       radius: 3
       spread: 1.0
       visible: panelMain.focus
   }
   Image
   {
       id:dpad
       anchors.centerIn: parent
       width: parent.width/4
       height: parent.height/4
       source: "qrc:/images/dpad.png"
        clip: false
   }
    opacity:1.0
}


