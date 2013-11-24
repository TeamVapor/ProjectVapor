# Add more folders to ship with the application, here
folder_01.source = qml/ProjectVapor
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Bonjour/bonjourserviceresolver.cpp \
    Bonjour/bonjourserviceregister.cpp \
    Bonjour/bonjourservicebrowser.cpp \
    Bonjour/qnsdmanager.cpp \
    Bonjour/vaporarcadensd.cpp \
    Settings/applicationsettings.cpp \
    Emulator/EmulatorCore.cpp \
    MessageServices/tcpserver.cpp \
    MessageServices/networkuser.cpp \
    MessageServices/networklobby.cpp \
    MessageServices/lobbymanager.cpp \
    MessageServices/chatconnection.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    ArtResources.qrc

OTHER_FILES += \
    qml/ProjectVapor/ChatHandler.js \
    qml/ProjectVapor/SettingsMenu.qml

HEADERS += \
    qnsdmanager.h \
    Bonjour/bonjourserviceresolver.h \
    Bonjour/bonjourserviceregister.h \
    Bonjour/bonjourservicebrowser.h \
    Bonjour/bonjourrecord.h \
    Bonjour/qnsdmanager.h \
    Emulator/EmulatorLauncher.h \
    Bonjour/vaporarcadensd.h \
    Settings/applicationsettings.h \
    Emulator/EmulatorCore.h \
    MessageServices/tcpserver.h \
    MessageServices/networkuser.h \
    MessageServices/networklobby.h \
    MessageServices/lobbymanager.h \
    MessageServices/iuser.h \
    MessageServices/ilobby.h \
    MessageServices/chatconnection.h

CONFIG += c++11


LIBS+=-ldns_sd
