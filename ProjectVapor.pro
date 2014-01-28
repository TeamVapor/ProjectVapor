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

TARGET = VaporArcade

QT += core quick network

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Settings/applicationsettings.cpp \
    Emulator/EmulatorCore.cpp \
    Emulator/EmulatorSettingsReader.cpp \
    vaporarcade.cpp \
    Network/Chat/chatconnection.cpp \
    Network/Chat/connectionmanager.cpp \
    Network/Chat/tcpserver.cpp \
    Network/Lobby/lobbymanager.cpp \
    Network/Lobby/networklobby.cpp \
    Network/Peer/networkuser.cpp \
    Network/Peer/peermanager.cpp \
    Network/Services/qnsdmanager.cpp \
    Network/Services/vaporarcadensd.cpp \
    Network/Services/Bonjour/bonjourservicebrowser.cpp \
    Network/Services/Bonjour/bonjourserviceregister.cpp \
    Network/Services/Bonjour/bonjourserviceresolver.cpp \
    Network/networkservices.cpp \
    Network/Chat/chatmessagefactory.cpp

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
    Emulator/EmulatorLauncher.h \
    Settings/applicationsettings.h \
    Emulator/EmulatorCore.h \
    Emulator/EmulatorSettingsReader.h \
    vaporarcade.h \
    Network/Chat/chatconnection.h \
    Network/Chat/connectionmanager.h \
    Network/Chat/tcpserver.h \
    Network/Interfaces/ichatconnection.h \
    Network/Interfaces/ilobby.h \
    Network/Interfaces/iuser.h \
    Network/Lobby/lobbymanager.h \
    Network/Lobby/networklobby.h \
    Network/Peer/networkuser.h \
    Network/Peer/peermanager.h \
    Network/Services/qnsdmanager.h \
    Network/Services/vaporarcadensd.h \
    Network/Services/Bonjour/bonjourrecord.h \
    Network/Services/Bonjour/bonjourservicebrowser.h \
    Network/Services/Bonjour/bonjourserviceregister.h \
    Network/Services/Bonjour/bonjourserviceresolver.h \
    Network/networkservices.h \
    Network/Interfaces/iMessageFactory.h \
    Network/Interfaces/iMessageParser.h \
    Network/Chat/chatmessagefactory.h

CONFIG += c++11


win32:LIBS += -L"E:\Program Files\Bonjour SDK" -ldnssd



linux:LIBS+=-ldns_sd

