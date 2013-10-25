//CTOR
function createInstance(parent,base_width,base_height,x,y, fit_fullscreen)
{
    var component = Qt.createComponent("ZoomSurface.qml");
    var surface = component.createObject(parent);
    surface.width = base_width;
    surface.height = base_height;
    surface.fit_fullscreen = fit_fullscreen;
    surface.x = x;
    surface.y = y;
    return surface;
}
var zoom_item = null;

// Item Manipulation functions
function addItem(surface,component_type,width,height,x,y)
{
    var component = Qt.createComponent(component_type);
    var _item = component.createObject(surface);
    _item.x = x;//Qt.binding(function() { return surface.x + x; });
    _item.y = y;//Qt.binding(function() { return surface.y + y; });
    _item.width = width;
    _item.height = height;
    _item.orig_w = width;
    _item.orig_h = height;
    _item.z = surface.backgroundImage.z+1;

    return _item;
}


