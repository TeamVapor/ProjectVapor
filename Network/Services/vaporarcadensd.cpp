#include "vaporarcadensd.h"
#include "Network/Peer/networkuser.h"
#include "Network/Lobby/networklobby.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QByteArray>
#include <QTcpServer>
static const char TerminationToken = 27;
VaporArcadeNSD::VaporArcadeNSD(QObject *parent, QQmlContext * context, QString username, bool use_NSD) :
    QObject(parent)
{
    mUserName = (username == "" ?  QHostInfo::localHostName():username); // or username if not an empty stringm
    mContext = context;
    if(use_NSD) // if system should use nsd
    {
        connect(&mLANPeerManager,SIGNAL(recordsChanged()),this,SLOT(lanUsersUpdated()));
        connect(&mLANPeerManager,SIGNAL(resolvedRecord(QHostInfo,int)),this,SLOT(userRecordResolved(QHostInfo,int)));
      //  connect(&mLANGameManager,SIGNAL(recordsChanged()),this,SLOT(lanLobbysUpdated()));
       // connect(&mLANGameManager,SIGNAL(resolvedRecord(QHostInfo,int)),this,SLOT(gameLobbyResolved(QHostInfo,int)));


        mLANPeerManager.setLocalName(mUserName+ "$$" + QHostInfo::localHostName());
        mLANPeerManager.registerService("Vapor Arcade Chat","_vaporarcade_peer._tcp",0);
        mLANPeerManager.browseService("_vaporarcade_peer._tcp");
      //  mLANGameManager.browseService("_vaporarcade_gl._tcp");
        mUserList.append(mUserName);

    }
    mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
   // mContext->setContextProperty("NSDGameLobbyList",QVariant::fromValue(mGameLobbyList));
    mContext->setContextProperty("LobbyManager",this);
   // connect(mServer,SIGNAL(newChatConnection(ChatConnection*)),this,SLOT(newConnection(ChatConnection*)));
  //  mMainLobby = new NetworkLobby(this,"MAIN",0);
}



bool VaporArcadeNSD::awareOfUserAlready(QString user)
{
    if(mCurrentRecordsResolving.contains(user))
        return true;
    foreach(const QVariant user_v, mUserList)
    {
        if(user_v == user)
            return true;
    }
    foreach(NetworkUser * nusr, mLANUsers)
    {
        if(nusr->getName() == user)
            return true;
    }

    return false;
}


QStringList VaporArcadeNSD::findUsersThatLeft(const QStringList &records)
{
    QStringList records_to_users;
    bool users_removed(false);
    foreach(QString record, records)
    {
        records_to_users.append(serviceNameToUsername(record));
    }

    foreach( QString rec_res, mCurrentRecordsResolving)
    {
        if(!records_to_users.contains(rec_res))
        {
            mCurrentRecordsResolving.removeOne(rec_res);
        }
    }
    foreach( NetworkUser * usr, mLANUsers)
    {
        qDebug() << usr->getName();
        if(!records_to_users.contains(usr->getName()))
        {

            mUserList.removeOne(QVariant(usr->getName()));
            if(!mLANUsers.removeOne(usr))
                qDebug() << "failed to remove user";
            qDebug() << usr->getName();
        }
    }
    if(users_removed)
        mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
    return records_to_users;
}


void VaporArcadeNSD::createGameLobby( QString lobbyname)
{
    //mLANGameManager.setLocalName(lobbyname);
    //mLANGameManager.registerService((lobbyname + "$$" + mUserName),"_vaporarcade_gl._tcp",mServer->serverPort());
}



void VaporArcadeNSD::gameLobbyResolved(QHostInfo info, int port)
{

}


QString VaporArcadeNSD::nickName() const
{
    //return QString(peerManager->userName()) + '@' + QHostInfo::localHostName()
        //   + ':' + QString::number(server.serverPort());
    return mUserName;
}


void VaporArcadeNSD::lanLobbysUpdated()
{
    //QStringList records = mLANGameManager.getServiceNames();
}

void VaporArcadeNSD::lanUsersUpdated()
{
    QStringList records = mLANPeerManager.getServiceNames();
    findUsersThatLeft(records);
    QString username;
    foreach(QString record,records)
    {
        username = (serviceNameToUsername(record));
        if(!awareOfUserAlready(username))
        {
            mCurrentRecordsResolving.append(username);
        }
    }
    if(mCurrentRecordsResolving.length() > 0)
    {
        // only use if demanding immediate stop
        //mLANPeerManager.forceStopResolving();
        mLANPeerManager.resolveServciceByType("_vaporarcade_peer._tcp.",records.first());
    }
}



void VaporArcadeNSD::resolveTimedOutLobby()
{

}

void VaporArcadeNSD::resolveTimedOutUser()
{

}



QString VaporArcadeNSD::serviceNameToUsername(QString hostname)
{
    QString username(hostname);
    username = username.split("$$")[0];
    return username;
}


void VaporArcadeNSD::userRecordResolved(QHostInfo info, int port)
{
    QString user(mCurrentRecordsResolving.first());
    mCurrentRecordsResolving.pop_front();
    QString username = user;
    user+=  '$'+info.hostName();
    qDebug() << username;
    qDebug() << user;
    if(username != mUserName)
    {
        QHostAddress addr(info.addresses()[0]);
        //ChatConnection* ccon = new ChatConnection(this,user,info,port);
        /*NetworkUser * netuser = new NetworkUser(this,username,ccon);
        if(!awareOfUserAlready(username))
        {
            mUserList.append(username);
            mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
        }
        mLANUsers.append(netuser);

        //ccon->connectToHost(addr, port);*/
    }
    if(mCurrentRecordsResolving.length() > 0)
        mLANPeerManager.resolveSercviceWithTypeAndNameContains(mCurrentRecordsResolving.first(),"_vaporarcade_peer._tcp.");

}

VaporArcadeNSD::~VaporArcadeNSD()
{
    for(int i = 0; i < mLANUsers.length(); i++)
    {
        NetworkUser * user = mLANUsers[i];
        user->deleteLater();
    }
    //delete mGameLobby;
    //delete mMainLobby;
}
