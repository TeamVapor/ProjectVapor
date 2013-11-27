import QtQuick 2.0
import QtGraphicalEffects 1.0
VaporRectangle {

    //property alias bookshelfBG: bookshelfBG
    id: bookshelfMain

    property ListModel gamesList: GameList{  }
    property var validIndexArray: []
    property int shelfcount: 7
    property int currentArrayIndex: 0
    property int gamesPerRow: 16
    property bool navigatingGames: false

    glowZ: -50
    scalable: false
    zScalable: false
    pressable: false

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
        currentIndex: -1
        anchors.topMargin: bookshelfMain.height/shelfcount *.08
        anchors.rightMargin: 16
        anchors.bottomMargin: 2
        cellHeight: bookshelfMain.height/shelfcount
        width: bookshelfMain.width *.75
        cellWidth:width/gamesPerRow
        height: bookshelfMain.height
        contentWidth: width
        contentHeight: height
        interactive: false
        delegate: Gamecase{}
        highlightRangeMode: GridView.StrictlyEnforceRange
        highlightFollowsCurrentItem:  false
        keyNavigationWraps: true
        onCurrentItemChanged: {
            if(currentItem)
            {
                var currenty = currentItem.mapToItem(null,0,0).y;
                if(currenty < 0)
                {
                    zoomsurface.moveto(zoomsurface.x,(zoomsurface.y -currenty) );
                }
                else if(currenty+cellHeight >= ScreenHeight)
                {
                    zoomsurface.moveto(zoomsurface.x,zoomsurface.y + (ScreenHeight - (currenty + currentItem.height)));
                }
            }
        }

        Keys.onLeftPressed: {
            event.accepted = true;
            moveCurrentIndexLeft();

        }
        Keys.onRightPressed:
        {
            event.accepted = true;
            moveCurrentIndexRight();
        }
        Keys.onDownPressed:
        {
            event.accepted = true;
            moveCurrentIndexDown();
        }
        Keys.onUpPressed:
        {
            event.accepted = true;
            moveCurrentIndexUp();
        }
        Keys.onBackPressed:
        {
            shelfGrid.focus = false;
            bookshelfMain.focus = true;
            currentIndex = -1;
        }
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
        }
        else if(event.key == Qt.Key_Backspace) {
            zoomsurface.zoomOutToFull();
            //shelfGrid.currentItem.focus = false;
            shelfGrid.focus = false;
            bookshelfMain.focus = true;
            navigatingGames = false;
            shelfGrid.currentIndex = -1;
        }
        else if(event.key == Qt.Key_Left) {
            bookshelfMain.focus = false;
            monitor.focus = true;
        }
    }
    transformOrigin: Item.TopLeft
}
