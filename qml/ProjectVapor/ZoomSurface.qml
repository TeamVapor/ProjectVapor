import QtQuick 2.0
import QtQuick.Window 2.0

/*****************************************************************
  ZoomSurface: Creates a zoomable surface area and
  ultimately just provides controlled animations.
 How-To Use: Create a ZoomSurface using the zoomablesurface.js
  function 'createInstance'. After storing the instance of zoomSurface
  add items and use the builtin zoom functions.
  ****************************************************************/

Rectangle {
    id:zoomsurface
    // Variables that control Zoom State and Animations
    property bool zoomedIn: true
    property var targetItem:undefined
    property real targetScale: 1
    property int targetX: 0
    property int targetY: 0
    property int targetWidth: 0
    property int targetHeight: 0
    // Variables that define the 'Norm' for ZoomSurface
    property bool fit_fullscreen:false
    property real scaledOutValue:1
    property var screen:undefined
    property alias backgroundImage:image
    Image
    {
        id: image
        anchors.fill: parent
        visible: false
    }
    function moveto(x,y)
    {
        targetX = x;
        targetY = y;
        targetItem = null;
        zoomToItemAnywhere.start();
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


    function zoomToAny(width,height,x,y)
    {

        targetItem = null;
        if( height >= 1080 && width >= 1920)
        {
            targetScale = 1080/width;
        }
        targetX = -((x )*(targetScale/ zoomsurface.scale));
        targetY = -( (y )*(targetScale/ zoomsurface.scale));
        zoomToItemAnywhere.start();
    }
    function zoomToAnyCentered(width,height,x,y)
    {

        targetItem = null;
        if( height >= 1080 && width >= 1920)
        {
            targetScale = 1080/width;
        }
        targetX = -((x )*   (targetScale/ zoomsurface.scale))+ 960;
        targetY = -( (y )* (targetScale/ zoomsurface.scale))+ 540;
        zoomToItemAnywhere.start();
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
    function zoomOut()
    {
        zoomOutAnimation.start();
    }

    function zoomOutToFull()
    {
        zoomOutFull.start();
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
        id: zoomOutAnimation
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
            if(zoomsurface.targetItem)
            {
                    zoomsurface.targetItem.onZoomedOutStopped();
            }
        }
    }
    ParallelAnimation{
        id: zoomInItemFull
        running: false
        onStarted:
        {
            if(zoomsurface.targetItem)
            {
                zoomsurface.targetItem.onStartZoomInFull();
            }
        }

        PropertyAnimation{
            target: zoomsurface
            easing.type: Easing.InCirc
            properties: "scale"
            to: 1.0
            duration: 600
        }
        PropertyAnimation{
            id: moveXFull
            target: zoomsurface
            properties: "x"
            to:  zoomsurface.targetItem ? -zoomsurface.targetItem.x:0
            duration: 600
            running: false
        }
        PropertyAnimation{
            id: moveYFull
            target: zoomsurface
            properties: "y"
            to:  zoomsurface.targetItem ? -zoomsurface.targetItem.y:0
            duration:600
            running: false
        }

        onStopped:
        {
            zoomsurface.zoomedIn = true;
            zoomsurface.fit_fullscreen = true;
        }
    }
    PropertyAnimation {
        id: stretchToFullW
        target: zoomsurface.targetItem ?  zoomsurface.targetItem:null
        properties: "width"
        to: zoomsurface.parent.width
        duration:300
        running: false
    }
    PropertyAnimation{
        id: stretchToFullH
        target: zoomsurface.targetItem ?  zoomsurface.targetItem:null
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
            target: zoomsurface.targetItem ?  zoomsurface.targetItem:null
            properties: "width"
            to:  zoomsurface.targetItem ? zoomsurface.targetItem.orig_w:0
            duration:600
        }
        PropertyAnimation{
            id: stretchToOrigH
            running: false
            target: zoomsurface.targetItem ?  zoomsurface.targetItem:null
            properties: "height"
            to:  zoomsurface.targetItem ? zoomsurface.targetItem.orig_h:0
            duration:600

        }

        onStopped:
        {
            zoomsurface.zoomedIn = false;
            zoomsurface.fit_fullscreen = false;
            if(zoomsurface.targetItem)
            {

                zoomsurface.targetItem.onZoomedOutStopped();

            }
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
            to:  zoomsurface.targetItem ? -(zoomsurface.targetItem.x +zoomToItemWithOffset.xOffset):0
            duration: 600
            running: false
        }
        PropertyAnimation{
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "y"
            to: zoomsurface.targetItem ? -(zoomsurface.targetItem.y + zoomToItemWithOffset.yOffset):0
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


    ParallelAnimation{
        id: zoomToItemAnywhere
        running: false
        onStarted:
        {
            if(zoomsurface.targetItem)
            {
                zoomsurface.targetItem.onZoomedInAnywhere();
            }
        }

        PropertyAnimation{
            target: zoomsurface
            easing.type: Easing.InOutCirc
            properties: "scale"
            to: targetScale
            duration: 600
        }
        PropertyAnimation{
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "x"
            to: targetX
            duration: 600
            running: false
        }
        PropertyAnimation{
            easing.type: Easing.InQuart
            target: zoomsurface
            properties: "y"
            to: targetY
            duration:600
            running: false
        }
        onStopped:
        {
            zoomsurface.zoomedIn = true;
            zoomsurface.fit_fullscreen = false;
            if(zoomsurface.targetItem)
            {
                zoomsurface.targetItem.onZoomedInStopped();
            }
        }
    }

}

