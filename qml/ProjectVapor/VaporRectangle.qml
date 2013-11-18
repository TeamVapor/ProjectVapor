import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    id: vaporRect

    //team vapor color theme
    property string alternateBase: "#3e519c"
    property string base: "#26305c"
    property string light: "#b3ccee"
    property string midlight: "#6681bd"
    property string mid: "#495c86"
    property string dark: "#3a4858"
    property string shadow: "#323c4d"
    property string text: "black"
    property string button: "#56699e"
    property string buttonText: "black"
    property string highlight: "#274bdb"
    property string highlightedText: "#5d77de"

    //enable/disable depending on object's usage
    property bool scalable: true
    property bool pressable: true

    //determines whether or not to display glow
    focus: false

    //interface aliases
    property alias glowOpacity: vaporGlow.opacity
    property alias glowZ: vaporGlow.z

    signal isPressed

    RectangularGlow
    {
        id: vaporGlow
        anchors.centerIn: parent.Center
        width: vaporRect.width * 1.01
        height: vaporRect.height * 1.01
        glowRadius: 15
        spread: 0.2
        color: light
        cornerRadius: vaporRect.radius + glowRadius
        visible: false
        z: vaporRect.z - 5
        opacity: 0.7
    }

    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return)
        {
            if (vaporRect.pressable && !event.isAutoRepeat)
            {
                vaporRect.state = "pressed";
            }
            event.accepted = true;
        }
    }

    Keys.onReleased:
    {
        if (event.key == Qt.Key_Return)
        {
            if (vaporRect.pressable)
                vaporRect.state = "selected";
            event.accepted = true;
        }
    }

    states:
    [
        State
        {
            name: ""
            when: focus == false
        },

        State
        {
            name: "selected"
            when: focus == true
            PropertyChanges
            {
                target: vaporRect
                explicit: true
                scale: scalable ? 1.05 : 1.00
                x: vaporRect.x
                z: vaporRect.z + 5
            }
            PropertyChanges
            {
                target: vaporGlow
                explicit: true
                visible: true
            }
        },

        State
        {
            name: "pressed"
            PropertyChanges {
                target: vaporGlow
                explicit: true
                glowRadius: 25
                spread: 0.3
                color: shadow
                cornerRadius: vaporRect.radius + glowRadius
                visible: true
                opacity: 0.5
            }
        }
    ]

    transitions:
    [
        Transition
        {
            from: "*"; to: "selected"
            ParallelAnimation
            {
                NumberAnimation { target: vaporRect; property: "scale"; from: 1.0; to: scalable ? 1.05 : 1.00; duration: 50; easing.type: Easing.InOutQuad }
                NumberAnimation { target: vaporGlow; property: "opacity"; from: 0.0; to: 0.7; duration: 50; easing.type: Easing.InOutQuad }
                NumberAnimation { target: vaporGlow; property: "spread"; from: 0.0; to: 1.0; duration: 50; easing.type: Easing.InOutQuad }
                NumberAnimation { target: vaporGlow; property: "spread"; from: 1.0; to: 0.2; duration: 50; easing.type: Easing.InOutQuad }
            }
        },

        Transition
        {
            from: "selected"; to: "*"
            ParallelAnimation
            {
                NumberAnimation { target: vaporRect; property: "scale"; from: scalable ? 1.05 : 1.00; to: 1.0; duration: 50; easing.type: Easing.InOutQuad }
                NumberAnimation { target: vaporGlow; property: "opacity"; from: 0.7; to: 0.0; duration: 50; easing.type: Easing.InOutQuad }
                NumberAnimation { target: vaporGlow; property: "spread"; from: 0.2; to: 0.0; duration: 50; easing.type: Easing.InOutQuad }
            }
        },

        Transition
        {
            from: "selected"; to: "pressed"
            ParallelAnimation
            {
                NumberAnimation { target: vaporGlow; property: "color"; from: light; to: shadow; duration: 50; easing.type: Easing.InOutQuad }
            }
        },

        Transition
        {
            from: "pressed"; to: "selected"
            ParallelAnimation
            {
                NumberAnimation { target: vaporGlow; property: "color"; from: shadow; to: light; duration: 50; easing.type: Easing.InOutQuad }
            }
        }
    ]
}
