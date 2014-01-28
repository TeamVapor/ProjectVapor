#include "Network/Lobby/lobbymanager.h"
#include "Network/Chat/tcpserver.h"
#include "Network/Peer/networkuser.h"
#include "Network/Lobby/networklobby.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QByteArray>
static const char TerminationToken = 27;
LobbyManager::LobbyManager(QObject *parent) :
    QObject(parent)
{
    mConnectedString = " connected to VaporChat Main Lobby.";
}




void LobbyManager::createGameLobby( QString lobbyname)
{

}



void LobbyManager::gameLobbyResolved(QHostInfo info, int port)
{

}




LobbyManager::~LobbyManager()
{

}
