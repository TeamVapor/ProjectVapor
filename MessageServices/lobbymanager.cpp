#include "lobbymanager.h"
#include "tcpserver.h"
#include "networkuser.h"
#include "networklobby.h"
#include <QQmlContext>
LobbyManager::LobbyManager(QObject *parent, QQmlContext * context, QString username, bool use_NSD) :
    QObject(parent), mServer(new TCPServer(this))
{
    mUserName = (username == "" ?  QHostInfo::localHostName():username); // or username if not an empty stringm
    qDebug() << mUserName;
    mContext = context;
    if(use_NSD) // if system should use nsd
    {
        connect(&mLANPeerManager,SIGNAL(recordsChanged()),this,SLOT(lanUsersUpdated()));
        connect(&mLANPeerManager,SIGNAL(resolvedRecord(QHostInfo,int)),this,SLOT(userRecordResolved(QHostInfo,int)));
        connect(&mLANGameManager,SIGNAL(recordsChanged()),this,SLOT(lanLobbysUpdated()));
        connect(&mLANGameManager,SIGNAL(resolvedRecord(QHostInfo,int)),this,SLOT(gameLobbyResolved(QHostInfo,int)));


        mLANPeerManager.setLocalName(mUserName);
        mLANPeerManager.registerService("Vapor Arcade Chat","_vaporarcade_peer._tcp",mServer->serverPort());
        mLANPeerManager.browseService("_vaporarcade_peer._tcp");
        mLANGameManager.browseService("_vaporarcade_gamelobby._tcp");

        mContext->setContextProperty("LobbyManager",this);
        mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
        mContext->setContextProperty("NSDGameLobbyList",QVariant::fromValue(mGameLobbyList));
    }
    connect(mServer,SIGNAL(newChatConnection(ChatConnection*)),this,SLOT(newConnection(ChatConnection*)));
    mMainLobby = new NetworkLobby(this,"MAIN",0);
}



bool LobbyManager::awareOfUserAlready(QString user)
{
    if(mCurrentRecordsResolving.contains(user))
        return true;
    foreach(const QVariant user_v, mUserList)
    {
        if(user_v == user)
            return true;
    }
    return false;
}

void LobbyManager::findUsersThatLeft(const QStringList &records)
{
    QStringList records_to_users;
    foreach(QString record, records)
    {
        records_to_users.append(serviceNameToUsername(record));
    }

    foreach( QString rec_res, mCurrentRecordsResolving)
    {
        if(!records_to_users.contains(rec_res))
            mCurrentRecordsResolving.removeOne(rec_res);
    }
}


void LobbyManager::gameLobbyResolved(QHostInfo info, int port)
{

}


QString LobbyManager::nickName() const
{
    //return QString(peerManager->userName()) + '@' + QHostInfo::localHostName()
        //   + ':' + QString::number(server.serverPort());
    return mUserName;
}

bool LobbyManager::hasConnection(const QHostAddress &senderIp, int senderPort) const
{
  //  if (senderPort == -1)
 //       return peers.contains(senderIp);

  //  if (!peers.contains(senderIp))
        return false;

  //  QList<ChatConnection *> connections = peers.values(senderIp);
  //  foreach (ChatConnection *connection, connections) {
  //      if (connection->peerPort() == senderPort)
  //          return true;
  //  }
//
    return false;
}

void LobbyManager::newConnection(ChatConnection *connection)
{
    //connection->setGreetingMessage(peerManager->userName());

   // connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
  //          this, SLOT(connectionError(QAbstractSocket::SocketError)));
  //  connect(connection, SIGNAL(disconnected()), this, SLOT(disconnected()));
  //  connect(connection, SIGNAL(readyForUse()), this, SLOT(readyForUse()));
}

void LobbyManager::readyForUse()
{
   // ChatConnection *connection = qobject_cast<ChatConnection *>(sender());
   // if (!connection || hasConnection(connection->peerAddress(),
  //                                   connection->peerPort()))
  //      return;

  //  connect(connection, SIGNAL(newMessage(QString,QString)),
  //          this, SIGNAL(newMessage(QString,QString)));

 //   peers.insert(connection->peerAddress(), connection);
 //   QString nick = connection->name();
 //   if (!nick.isEmpty())
 //       emit newParticipant(nick);
}

void LobbyManager::disconnected()
{
    if (ChatConnection *connection = qobject_cast<ChatConnection *>(sender()))
        removeConnection(connection);

}

void LobbyManager::connectionError(QAbstractSocket::SocketError /* socketError */)
{
   // if (ChatConnection *connection = qobject_cast<ChatConnection *>(sender()))
   //     removeConnection(connection);
}

void LobbyManager::lanLobbysUpdated()
{

}

void LobbyManager::lanUsersUpdated()
{
    QStringList records = mLANPeerManager.getServiceNames();
    findUsersThatLeft(records);
    foreach(QString record,records)
    {
        if(!awareOfUserAlready(record))
        {
            mCurrentRecordsResolving.append(serviceNameToUsername(record));
        }
    }
    if(mUserList.length() == 0 && records.length() > 0)
        mLANPeerManager.resloveServiceAtIndex(0);
}




void LobbyManager::removeConnection(ChatConnection *connection)
{
   foreach(NetworkUser * user, mLANUsers)
   {
       if(user->getConnection() == connection)
       {
           mLANUsers.removeOne(user);
       }
   }

   //     peers.remove(connection->peerAddress());
   //     QString nick = connection->name();
   //     if (!nick.isEmpty())
  //          emit participantLeft(nick);
   // }
  //  connection->deleteLater();
}


void LobbyManager::resolveTimedOutLobby()
{

}

void LobbyManager::resolveTimedOutUser()
{

}

void LobbyManager::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    //QList<ChatConnection *> connections = peers.values();
    //foreach (ChatConnection *connection, connections)
    //    connection->sendMessage(message);
}


QString LobbyManager::serviceNameToUsername(QString hostname)
{
    QString username(hostname);
    username = username.split(" on ")[0];
    return username;
}


void LobbyManager::userRecordResolved(QHostInfo info, int port)
{
    QString user(mCurrentRecordsResolving.front());
    mCurrentRecordsResolving.pop_front();
    mUserList.append(QVariant(user));
    mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
    if(user == mUserName)
    {
        //setHostInfo(info, port);
    }
    else
    {
        NetworkUser * net_user = new NetworkUser(this,user,info,port);
        mLANUsers.append(net_user);
        ChatConnection* ccon = new ChatConnection(net_user,info.hostName());
        net_user->setConnection(ccon);
        emit newConnection(ccon);
        mMainLobby->addUser(net_user);
        ccon->connectToHost(info.addresses()[0], port);
    }
    // create a chat connection and a NetworkUser
    // add the new user to mainLobby
    // send announce message

}

LobbyManager::~LobbyManager()
{
    if(mServer)
        delete mServer;
}
