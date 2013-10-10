import QtQuick 2.0

Rectangle {
    //property alias bookshelfBG: bookshelfBG
    id: bookshelfMain
    property ListModel gamesList: GameList{  }

    Image{
        id: bookshelfTop
        source:"qrc:/images/bookshelftop.png"
        anchors.top: parent.top
        height: (parent.height/11) * 1.229
        width: parent.width
    }
    Column{
        anchors.top: bookshelfTop.bottom

        Repeater{
            model: 9
            Image{
                width: bookshelfMain.width
                height: (bookshelfMain.height- bookshelfTop.height)/10
                source: "qrc:/images/bookshelfshelf.png"
                ListView{

                }
            }
        }
    }
    Image{
        id: bookshelfBottom
        source:"qrc:/images/bookshelfbottom.png"
        anchors.bottom: parent.bottom
        height: (bookshelfMain.height- bookshelfTop.height)/10
        width: parent.width
    }
}
