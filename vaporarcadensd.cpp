#include "vaporarcadensd.h"
#include <QQmlContext>
VaporArcadeNSD::VaporArcadeNSD(QObject *parent, QString Username) :
    QObject(parent)
{
    connect(&mChatBrowser,SIGNAL(recordsChanged()),this,SLOT(userRecordsChanged()));
    connect(&mGameBrowser,SIGNAL(recordsChanged()),this,SLOT(gameRecordsChanged()));
    mChatBrowser.setLocalName(Username);
    mChatBrowser.registerService("Vapor Arcade Chat","_vaporarcade_chat._tcp",0);
    beginBrowsingUsers();
    beginBrowsingLobbies();
}

void VaporArcadeNSD::beginBrowsingLobbies()
{
    mGameBrowser.browseService("_vaporarcade_gamelobby._tcp");
}

void VaporArcadeNSD::beginBrowsingUsers()
{
    mChatBrowser.browseService("_vaporarcade_chat._tcp");
}


void VaporArcadeNSD::gameRecordsChanged()
{
    mGameLobbyList.clear();
    QStringList names = mGameBrowser.getServiceNames();
    foreach(QString  name, names)
    {
        mGameLobbyList.append(name.left(name.indexOf(" on")));
    }
    mContext->setContextProperty("NSDGameLobbyList",QVariant::fromValue(mGameLobbyList));

}

void VaporArcadeNSD::setContext(QQmlContext *context)
{
    mContext = context;
    mContext->setContextProperty("NSDServices",this);
    mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
    mContext->setContextProperty("NSDGameLobbyList",QVariant::fromValue(mGameLobbyList));
}


void VaporArcadeNSD::startGameLobby(QString lobbyname)
{
    mGameBrowser.setLocalName(lobbyname);
    mGameBrowser.registerService("Vapor Arcade Game Lobby","_vaporarcade_gamelobby._tcp",0);
}


void VaporArcadeNSD::userRecordsChanged()
{
    mUserList.clear();
    QStringList names = mChatBrowser.getServiceNames();
    foreach(QString  name, names)
    {
        mUserList.append(name.left(name.indexOf(" on ")));
    }
    mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
}
