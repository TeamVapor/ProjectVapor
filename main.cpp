#include <QtGui/QScreen>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QtQuick/QQuickView>
#include "Emulator/EmulatorLauncher.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include "Bonjour/vaporarcadensd.h"
#include "Settings/applicationsettings.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScreen * pscreen = app.primaryScreen();
    QtQuick2ApplicationViewer viewer;
    viewer.setScreen(pscreen);
    bool showexpanded(true);
    //showexpanded = false; // Uncomment for FULLSCREEN
    int screen_width;
    int screen_height;
    if(!showexpanded)
    {
        screen_width = pscreen->size().width();
        screen_height = pscreen->size().height();
    }
    else
    {
        screen_width = pscreen->geometry().width();
        screen_height = pscreen->geometry().height();
    }

    viewer.rootContext()->setContextProperty("ScreenWidth", screen_width);
    viewer.rootContext()->setContextProperty("ScreenHeight",screen_height);
    ApplicationSettings settings;
    VaporArcadeNSD vpnsd(&app, settings.getUserName());
    viewer.rootContext()->setContextProperty("AppSettings",&settings);
    vpnsd.setContext(viewer.rootContext());
    qmlRegisterType<EmulatorLauncher>("com.vapor.project", 1, 0, "EmulatorLauncher");
    viewer.setMainQmlFile(QStringLiteral("qml/ProjectVapor/main.qml"));
    if(!showexpanded)
        viewer.showFullScreen();
    else
        viewer.showExpanded();
    return app.exec();
}
