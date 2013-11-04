import QtQuick 2.0
import QtGraphicalEffects 1.0

ZoomItem {

    //property alias bookshelfBG: bookshelfBG
    id: bookshelfMain

    property ListModel gamesList: GameList{  }
    property var validIndexArray: []
    property int shelfcount: 0
    property int currentArrayIndex: 0
    property int gamesPerRow: 16
    property bool navigatingGames: false
    height: parent.height
    Column{
        anchors.bottom: parent.bottom
        anchors.fill: parent
        Repeater{
            model: shelfcount
            Image{
                id: shelfImage
                width: bookshelfMain.width
                height: bookshelfMain.height/shelfcount
                source: "qrc:/images/bookshelfshelf.png"
            }

        }
    }
    GridView
    {
        id: shelfGrid
        model: gamesList
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.topMargin: bookshelfMain.height/shelfcount *.08
        anchors.rightMargin: 16
        anchors.bottomMargin: 2
        cellHeight: bookshelfMain.height/shelfcount
        width: bookshelfMain.width *.75
        cellWidth:width/gamesPerRow
        height: bookshelfMain.height
        highlight: Rectangle
        {
          width: shelfGrid.cellWidth
          height: shelfGrid.cellHeight * .92
          x: shelfGrid.currentItem.x
          y: shelfGrid.currentItem.y
          color: "transparent"
          border.color: "yellow"
          border.width: 2
          z: shelfGrid.z + gamesList.count;
        }

        delegate: Gamecase{}
        highlightRangeMode: GridView.StrictlyEnforceRange
        Keys.onLeftPressed: {
            event.accepted = true;
            moveSelectionLeft();
        }
        Keys.onRightPressed:
        {
            event.accepted = true;
            moveSelectionRight();
        }
        Keys.onDownPressed:
        {
            event.accepted = true;
            moveSelectionLeft();
        }
        Keys.onUpPressed:
        {
            event.accepted = true;
            moveSelectionRight();
        }
        Keys.onBackPressed:
        {
            shelfGrid.focus = false;
            bookshelfMain.focus = true;
        }

        keyNavigationWraps: false
        highlightFollowsCurrentItem: false
    }
    Rectangle
    {
        id: highlight
        anchors.fill: parent
        color:"transparent"
        border.color: "yellow"
        border.width: 16
        visible: bookshelfMain.focus

    }
    Keys.onPressed:
    {
        if (event.key == Qt.Key_Return) {
            if(navigatingGames == false)
            {
                zoomsurface.zoomToItemTopRight(bookshelf)
                shelfGrid.currentIndex = 0;
                shelfGrid.focus = true;
                bookshelfMain.focus = false;
                navigatingGames = true;
            }
            else
            {
                shelfGrid.currentItem.start();
            }

            //highlight.visible = false;
        }
        else if(event.key == Qt.Key_Backspace) {
            zoomsurface.zoomOutToFull();
            shelfGrid.focus = false;
            bookshelfMain.focus = true;
            navigatingGames = false;
            shelfGrid.currentIndex = 0;
        }
        else if(event.key == Qt.Key_Left) {
            bookshelfMain.focus = false;
            monitor.focus = true;
        }
    }
    function moveSelectionRight()
    {
        if(bookshelfMain.currentArrayIndex < bookshelfMain.validIndexArray.length)
        {
            shelfGrid.currentIndex = validIndexArray[++currentArrayIndex];
            shelfGrid.currentItem.focus = true;
        }
    }
    function moveSelectionLeft()
    {
        if(bookshelfMain.currentArrayIndex > 0)
        {
            shelfGrid.currentIndex = validIndexArray[--currentArrayIndex];
            shelfGrid.currentItem.focus = true;
        }
    }

    transformOrigin: Item.TopLeft
}
