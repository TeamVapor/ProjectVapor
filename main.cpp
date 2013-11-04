#include <QtGui/QScreen>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QtQuick/QQuickView>
#include "EmulatorLauncher.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include "vaporarcadensd.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScreen * pscreen = app.primaryScreen();
    QtQuick2ApplicationViewer viewer;
    int screen_width = pscreen->geometry().width();
    int screen_height = pscreen->geometry().height();
    viewer.rootContext()->setContextProperty("ScreenWidth", screen_width);
    viewer.rootContext()->setContextProperty("ScreenHeight",screen_height);
    VaporArcadeNSD vpnsd(&app);
    vpnsd.setContext(viewer.rootContext());
    qmlRegisterType<EmulatorLauncher>("com.vapor.project", 1, 0, "EmulatorLauncher");
    viewer.setMainQmlFile(QStringLiteral("qml/ProjectVapor/main.qml"));
    viewer.showFullScreen();
    //viewer.showExpanded();
    return app.exec();
}
