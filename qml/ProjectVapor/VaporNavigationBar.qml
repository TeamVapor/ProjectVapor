import QtQuick 2.0

VaporRectangle
{
    id: navigationContainer
    height: 0
    width: 0
    color: base
    anchors.bottom: parent.bottom
    opacity: 0.8
    visible: true

    property string upText: "Up"
    property string downText: "Down"
    property string leftText: "Left"
    property string rightText: "Right"
    property string redText: "Back"
    property string blueText: ""
    property string yellowText: "Accept"
    property string greenText: ""
    property string startText: ""
    property string selectText: ""

    property string upButton: "qrc:/images/up_button.png"
    property string downButton: "qrc:/images/down_button.png"
    property string leftButton: "qrc:/images/left_button.png"
    property string rightButton: "qrc:/images/right_button.png"
    property string redButton: "qrc:/images/red_button.png"
    property string blueButton: "qrc:/images/blue_button.png"
    property string yellowButton: "qrc:/images/yellow_button.png"
    property string greenButton: "qrc:/images/green_button.png"
    property string startSelectButton: "qrc:/images/start_select_button.png"

    property bool showUp: true
    property bool showDown: true
    property bool showLeft: true
    property bool showRight: true
    property bool showRed: true
    property bool showBlue: false
    property bool showYellow: true
    property bool showGreen: false
    property bool showStart: false
    property bool showSelect: false

    Row
    {
        id: directionalRow
        height: parent.height
        width: parent.width / 2
        anchors.top: parent.top
        anchors.left: parent.left

        VaporNavigationIcon
        {
            id: upIcon
            height: parent.height * 0.95
            width: (parent.width / 4) * 0.95
            visible: showUp
            source: upButton
            iconString: upText
        }
        VaporNavigationIcon
        {
            id: downIcon
            height: parent.height * 0.95
            width: (parent.width / 4) * 0.95
            visible: showDown
            source: downButton
            iconString: downText
        }
        VaporNavigationIcon
        {
            id: leftIcon
            height: parent.height * 0.95
            width: (parent.width / 4) * 0.95
            visible: showLeft
            source: leftButton
            iconString: leftText
        }
        VaporNavigationIcon
        {
            id: rightIcon
            height: parent.height * 0.95
            width: (parent.width / 4) * 0.95
            visible: showRight
            source: rightButton
            iconString: rightText
        }
    }

    Row
    {
        id: buttonRow
        height: parent.height
        width: parent.width / 2
        anchors.top: parent.top
        anchors.left: directionalRow.right

        VaporNavigationIcon
        {
            id: redIcon
            height: parent.height * 0.95
            width: (parent.width / 6) * 0.95
            visible: showRed
            source: redButton
            iconString: redText
        }
        VaporNavigationIcon
        {
            id: blueIcon
            height: parent.height * 0.95
            width: (parent.width / 6) * 0.95
            visible: showBlue
            source: blueButton
            iconString: blueText
        }
        VaporNavigationIcon
        {
            id: yellowIcon
            height: parent.height * 0.95
            width: (parent.width / 6) * 0.95
            visible: showYellow
            source: yellowButton
            iconString: yellowText
        }
        VaporNavigationIcon
        {
            id: greenIcon
            height: parent.height * 0.95
            width: (parent.width / 6) * 0.95
            visible: showGreen
            source: greenButton
            iconString: greenText
        }
        VaporNavigationIcon
        {
            id: startIcon
            height: parent.height * 0.95
            width: (parent.width / 6) * 0.95
            visible: showStart
            source: startSelectButton
            iconString: startText
        }
        VaporNavigationIcon
        {
            id: selectIcon
            height: parent.height * 0.95
            width: (parent.width / 6) * 0.95
            visible: showSelect
            source: startSelectButton
            iconString: selectText
        }
    }
    //vaporNavigationBar = ZoomSurface.addItem(zoomsurface, "VaporNavigationBar.qml", zoomsurface_width, zoomsurface_height * 0.05, 0, zoomsurface_height * 0.95);
    function centerIn(parent)
    {
        navigationContainer.height = parent.height * 0.05;
        navigationContainer.width = parent.width;
        navigationContainer.anchors.bottom = parent.bottom;
        navigationContainer.anchors.horizontalCenter = parent.horizontalCenter;
        navigationContainer.z = parent.z + 100;
    }

    function netLobbyNavigationSetup ()
    {

        upText = "Up";
        downText = "Down";
        leftText = "Left";
        rightText = "Right";
        redText = "Back";
        blueText = "";
        yellowText = "Accept";
        greenText = "";
        startText = "";
        selectText = "";

        showUp = true;
        showDown = true;
        showLeft = true;
        showRight = true;
        showRed = true;
        showBlue = false;
        showYellow = true;
        showGreen = false;
        showStart = false;
        showSelect = false;
    }

    function homeScreenNavigationSetup ()
    {
        upText = "Up"
        downText = "Down"
        leftText = "Left"
        rightText = "Right"
        redText = "Back"
        blueText = ""
        yellowText = "Accept"
        greenText = ""
        startText = ""
        selectText = ""

        showUp = true
        showDown = true
        showLeft = true
        showRight = true
        showRed = true
        showBlue = false
        showYellow = true
        showGreen = false
        showStart = false
        showSelect = false
    }

    function settingsNavigationSetup ()
    {
        upText = "Up"
        downText = "Down"
        leftText = "Left"
        rightText = "Right"
        redText = "Back"
        blueText = ""
        yellowText = "Accept"
        greenText = ""
        startText = ""
        selectText = ""

        showUp = true
        showDown = true
        showLeft = true
        showRight = true
        showRed = true
        showBlue = false
        showYellow = true
        showGreen = false
        showStart = false
        showSelect = false
    }

    function gameLobbyNavigationSetup ()
    {
        upText = "Up"
        downText = "Down"
        leftText = "Left"
        rightText = "Right"
        redText = "Red"
        blueText = "Blue"
        yellowText = "Yellow"
        greenText = "Green"
        startText = "Start"
        selectText = "Select"

        showUp = true
        showDown = true
        showLeft = true
        showRight = true
        showRed = true
        showBlue = true
        showYellow = true
        showGreen = true
        showStart = true
        showSelect = true
    }
}
