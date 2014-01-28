#include <QtGui/QScreen>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QtQuick/QQuickView>
#include "Emulator/EmulatorLauncher.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include "Network/Services/vaporarcadensd.h"
#include "Settings/applicationsettings.h"
#include "Network/Lobby/lobbymanager.h"
#include "vaporarcade.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScreen * pscreen = app.primaryScreen();
    QtQuick2ApplicationViewer viewer;
    viewer.setScreen(pscreen);
    bool showexpanded(true);
    showexpanded = false; // Uncomment for FULLSCREEN
    int screen_width;
    int screen_height;
    if(!showexpanded)
    {
        screen_width = pscreen->size().width();
        screen_height = pscreen->size().height();
    }
    else
    {
        screen_width = pscreen->availableGeometry().width();
        screen_height = pscreen->availableGeometry().height();
    }
    viewer.rootContext()->setContextProperty("ScreenWidth", screen_width);
    viewer.rootContext()->setContextProperty("ScreenHeight",screen_height);
    VaporArcade varcade;
    //LobbyManager lman(&app);
    viewer.rootContext()->setContextProperty("VaporArcade",&varcade);
    //qmlRegisterType<VaporArcade>("com.vapor.project", 1, 0, "VaporArcade");
    viewer.setMainQmlFile(QStringLiteral("qml/ProjectVapor/main.qml"));
    if(!showexpanded)
        viewer.showFullScreen();
    else
        viewer.showExpanded();
    return app.exec();
}
