import QtQuick 2.1
import QtQuick.Window 2.0
import "ZoomableSurface.js" as ZoomSurface


Rectangle {
    id: homeScreen
    width: ScreenWidth
    height: ScreenHeight
    property var zoomsurface: undefined
    property var gameList: undefined
    property var bookshelf: undefined
    property var desk: undefined
    property var monitor: undefined
    property var router: undefined
    property var netLobby: undefined
    property var gameLobby: undefined
    property var settingsMenu: undefined
    property var poster: undefined
    property var controllerBin: undefined
    property var vaporMessageDialog: undefined
    property var vaporInputDialog: undefined
    property var vaporNavigationBar: undefined
    property int shelfcount: 0
    property int screenwidth: ScreenWidth
    property int screenheight: ScreenHeight
    property int screenmultiplier: 0
    property int gamespershelfcount: 0
    color: "blue"
    scale: 1.0

    Image
    {
        id: mainBackground
        width: ScreenWidth
        height: ScreenHeight
        fillMode: Image.Tile
        source: "qrc:/images/wall_texture.jpg"
    }



    SIPKeyboard
    {
        id:sipKeyboard
        z: 100
        visible: false
    }

    Behavior on x
    {
        SmoothedAnimation
        {
            duration: 700
            alwaysRunToEnd: true
        }
    }

    Behavior on scale
    {
        SmoothedAnimation
        {
            velocity: 4.8
            alwaysRunToEnd: true
        }
    }

    Component.onCompleted:
    {
        // fill gameList from SQL database
        gameList = fetchGamesLibrary();
        calculateScreenSize();
        var zoomsurface_width = homeScreen.screenwidth * 2;
        var zoomsurface_height = homeScreen.screenheight * 2;
        zoomsurface = ZoomSurface.createInstance(homeScreen,ScreenWidth,ScreenHeight,zoomsurface_width,zoomsurface_height,0,0,false);
        zoomsurface.setBackgroundImage("qrc:/images/wall_texture.jpg");
        zoomsurface.backgroundImage.fillMode = Image.Tile;
        bookshelf = ZoomSurface.addItem(zoomsurface,"Bookshelf.qml",zoomsurface.width/4, zoomsurface_height,zoomsurface.width * .75 ,0);
        bookshelf.gamesPerRow = 20;
        bookshelf.shelfcount = gameList.count/20;
        bookshelf.anchors.right = zoomsurface.right;
        bookshelf.anchors.bottom = zoomsurface.bottom
        desk = ZoomSurface.addItem(zoomsurface,"ZoomImage.qml",zoomsurface.width/2,zoomsurface.height/2,zoomsurface/4,zoomsurface.height/2);
        desk.image.fillMode = Image.Stretch;
        desk.anchors.bottom = zoomsurface.bottom;
        desk.anchors.right = bookshelf.left;
        desk.anchors.rightMargin = 64;
        desk.image.source = "qrc:/images/desk.png";
        zoomsurface.color = "blue";
        monitor = ZoomSurface.addItem(zoomsurface,"Monitor.qml",desk.width * .6,zoomsurface.height/4,desk.x + (desk.width * .20),zoomsurface.height/4);
        monitor.anchors.bottom = desk.top;
        bookshelf.focus = false;
        monitor.focus = true;
        router = ZoomSurface.addItem(zoomsurface, "Router.qml",desk.width/4, monitor.height/5,desk.x+4, desk.y - (monitor.height/5));
        router.anchors.bottom = desk.top;
        router.anchors.bottomMargin = -2;
        router.z = desk.z+1;
        monitor.z = router.z+1;
        netLobby = ZoomSurface.addItem(zoomsurface, "NetLobby.qml", screenwidth, screenheight, 0, 0);
        netLobby.z = 100;
        netLobby.visible = false;
        gameLobby = ZoomSurface.addItem(zoomsurface, "GameLobby.qml", screenwidth, screenheight, 0, 0);
        gameLobby.z = 100;
        gameLobby.visible = false;
        controllerBin = ZoomSurface.addItem(zoomsurface, "ControllerBin.qml", zoomsurface_width * 0.28, zoomsurface_height * 0.5, 0, zoomsurface_height * 0.5);
        controllerBin.visible = true;
        settingsMenu = ZoomSurface.addItem(zoomsurface, "SettingsMenu.qml", screenwidth, screenheight, 0, 0);
        settingsMenu.z = 100;
        settingsMenu.visible = false;
        poster = ZoomSurface.addItem(zoomsurface, "Poster.qml", zoomsurface_width*.25, zoomsurface_height* .4, zoomsurface_width * .01, zoomsurface_height * .01);
        poster.visible = true;
        vaporMessageDialog = ZoomSurface.addItem(zoomsurface, "VaporMessageDialog.qml", screenwidth * 0.35, screenheight * 0.3, screenwidth * 0.32, screenheight * 0.35);
        vaporMessageDialog.visible = false;
        vaporInputDialog = ZoomSurface.addItem(zoomsurface, "VaporInputDialog.qml", screenwidth * 0.35, screenheight * 0.3, screenwidth * 0.32, screenheight * 0.35);
        vaporInputDialog.visible = false;
        vaporNavigationBar = ZoomSurface.addItem(zoomsurface, "VaporNavigationBar.qml", zoomsurface_width, zoomsurface_height * 0.05, 0, zoomsurface_height * 0.95);
        vaporNavigationBar.visible = true;
        //emuLauncher.setEmulatorSystemDir(AppSettings.getEmulatorDirectory());
        //emuLauncher.setRomsDir(AppSettings.getRomDirectory());
        zoomsurface.scaledOutValue = screenwidth/zoomsurface.width;
        zoomsurface.zoomOutToFull();
    }

    // Functions used for calculating the start of the applications

    // Fetch game library and fill game list
    function fetchGamesLibrary ()
    {
        //get game list elements from sql db
        var component = Qt.createComponent("GameList.qml");
        var gamelist = component.createObject(homeScreen);
        return gamelist;
    }

    function calculateScreenSize()
    {
        // calculate the amount of shelves needed for the original size
        var bookshelf_width = homeScreen.screenwidth/4;
        var shelf_width = bookshelf_width * .8;

        // calculate the amount of books that can fit on the shelf
        var game_count_per_shelf = shelf_width/32;
        // Amount of shelves needed to accomodate the books
        //multiplier tracks how many times the size will need to be
        //doubled for the bookshelf to contain 10 or less shelves
        var multiplier = 1;
        var shelf_count = homeScreen.gameList.count/ game_count_per_shelf;
        if( shelf_count > 14)
        {
            multiplier = 0;
            while( shelf_count >14)
            {
                shelf_count /= 2;
                multiplier += 2;
            }
        }
        // multiplier now contains the correct size for the zoomsurface
        homeScreen.screenmultiplier = multiplier;
        homeScreen.shelfcount = shelf_count;
        homeScreen.gamespershelfcount = game_count_per_shelf;
    }
}





