import QtQuick 2.0
import QtQuick.Window 2.0

Rectangle {
    id:zoomsurface
    property bool fit_fullscreen:false
    property var screen:undefined
    property bool zoomedIn: false
    property var targetItem:undefined
    property alias zoomOut:zoomOut
    property alias zoomOutFull:zoomOutFull
    property real scaledOutValue:1
    property alias backgroundImage:image
    Image
    {
        id: image
        anchors.fill: parent
        visible: false
    }
    function setBackgroundImage(img_path)
    {
        image.source = img_path;
        image.visible = true;
    }

    function zoomToItemTopLeft(item)
    {
        targetItem = item;
        zoomToItemWithOffset.xOffset =  0;
        zoomToItemWithOffset.yOffset = 0;
        zoomToItemWithOffset.start();
    }
    function zoomToItemTopRight(item)
    {
        targetItem = item;
        zoomToItemWithOffset.xOffset =  (item.width - ScreenWidth);
        zoomToItemWithOffset.yOffset = 0;
        zoomToItemWithOffset.start();
    }

    function zoomToItemCentered(item)
    {
        targetItem = item;
        zoomToItemWithOffset.xOffset =  -(ScreenWidth- item.width)/2;
        zoomToItemWithOffset.yOffset =  -(ScreenHeight- item.height)/2;
        zoomToItemWithOffset.start();
    }

    function zoomToItemFull(item)
    {
        targetItem = item;
        item.width = zoomsurface.parent.width;
        item.height = zoomsurface.parent.height;
        if(zoomedIn)
        {
            zoomOutThenInItem.start();
        }
        else
        {
            zoomInItemFull.start();
        }
    }

    function zoomToFullWidthTop(item)
    {
        targetItem = item;
        zoomToItemWithOffset.xOffset = 0;
        zoomToItemWithOffset.yOffset = 0;
        zoomToItemWithOffset.start();
        item.width = ScreenWidth;
    }
    transformOrigin: Item.TopLeft
    SequentialAnimation{

        id: zoomOutThenInItem
        onRunningChanged:
        {
            if(running)
            {
                zoomsurface.targetItem.onZoomedIn();
            }
        }
        ParallelAnimation{
            id: zoomOutItem
            PropertyAnimation{
                target: zoomsurface
                easing.type: Easing.InOutCirc
                properties: "scale"
                to: .2
                duration: 600
            }
            PropertyAnimation{
                id: moveXToZero
                easing.type: Easing.InQuart
                target: zoomsurface
                properties: "x"
                to: 0
                duration: 600

            }
            PropertyAnimation{
                id: moveYToZero
                easing.type: Easing.InQuart
                target: zoomsurface
                properties: "y"
                to: 0
                duration:600

            }
            onStopped:
            {
                zoomsurface.zoomedIn = false;
            }
        }
    }

    ParallelAnimation{
        id: zoomOut
        PropertyAnimation{
            target: zoomsurface
            easing.type: Easing.InOutCirc
            properties: "scale"
            to: zoomsurface.scaledOutValue
            duration: 600
        }
        PropertyAnimation{
            id: xToZero
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "x"
            to: 0
            duration: 600

        }
        PropertyAnimation{
            id: yToZero
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "y"
            to: 0
            duration:600

        }
        onStopped:
        {
           zoomsurface.zoomedIn = false;
           zoomsurface.targetItem.onZoomedOutStopped();
        }
    }
    ParallelAnimation{
        id: zoomInItemFull
        onStarted:
        {
            zoomsurface.targetItem.onStartZoomInFull();
          //  stretchToFullW.start();
          //  stretchToFullH.start();
        }

        PropertyAnimation{
            target: zoomsurface
            easing.type: Easing.bezierCurve
            properties: "scale"
            to: 1.0
            duration: 600
        }
        PropertyAnimation{
            id: moveXFull
            target: zoomsurface
            properties: "x"
            to: -zoomsurface.targetItem.x
            duration: 600
            running: false
        }
        PropertyAnimation{
            id: moveYFull
            target: zoomsurface
            properties: "y"
            to: -zoomsurface.targetItem.y
            duration:600
            running: false
        }

        onStopped:
        {
            zoomsurface.zoomedIn = true;
            zoomsurface.fit_fullscreen = true;
            console.log("Zoomsurface.x: " +  zoomsurface.x);
            console.log("Zoomsurface.y: " +  zoomsurface.y);
            console.log("targetitem.x: " +  zoomsurface.targetItem.x);
            console.log("targetitem.y: " +  zoomsurface.targetItem.y);
        }
    }
    PropertyAnimation {
        id: stretchToFullW
        target: zoomsurface.targetItem
        properties: "width"
        to: zoomsurface.parent.width
        duration:300
        running: false
    }
    PropertyAnimation{
        id: stretchToFullH
        target: zoomsurface.targetItem
        properties: "height"
        to: zoomsurface.parent.height
        duration:300
        running: false
    }
    ParallelAnimation{
        id: zoomOutFull
        running: false
        PropertyAnimation{
            target: zoomsurface
            easing.type: Easing.InOutCirc
            properties: "scale"
            to: zoomsurface.scaledOutValue
            duration: 600
        }
        PropertyAnimation{
            id: xToZeroFull
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "x"
            to: 0
            duration: 600

        }
        PropertyAnimation{
            id: yToZeroFull
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "y"
            to: 0
            duration:600

        }
        PropertyAnimation {
            id: stretchToOrigW
            target: zoomsurface.targetItem
            properties: "width"
            to: zoomsurface.targetItem.orig_w
            duration:600
        }
        PropertyAnimation{
            id: stretchToOrigH
            running: false
            target: zoomsurface.targetItem
            properties: "height"
            to: zoomsurface.targetItem.orig_h
            duration:600

        }

        onStopped:
        {
            zoomsurface.zoomedIn = false;
            zoomsurface.fit_fullscreen = false;
        }
    }


    // ZOOM IN ANYWHERE
    ParallelAnimation{
        id: zoomToItemWithOffset
        property int xOffset: 0
        property int yOffset: 0
        running: false
        onStarted:
        {
            zoomsurface.targetItem.onZoomedIn();
        }

        PropertyAnimation{
            target: zoomsurface
            easing.type: Easing.InOutCirc
            properties: "scale"
            to: 1.0
            duration: 600
        }
        PropertyAnimation{
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "x"
            to: -(zoomsurface.targetItem.x +zoomToItemWithOffset.xOffset)
            duration: 600
            running: false
        }
        PropertyAnimation{
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "y"
            to: -(zoomsurface.targetItem.y + zoomToItemWithOffset.yOffset)
            duration:600
            running: false
        }
        onStopped:
        {
            zoomsurface.zoomedIn = true;
            zoomsurface.fit_fullscreen = false;
            zoomsurface.targetItem.onZoomedInStopped();
        }
    }






}

