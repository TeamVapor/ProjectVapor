#include "lobbymanager.h"
#include "tcpserver.h"
#include "networkuser.h"
#include "networklobby.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QByteArray>
static const char TerminationToken = 27;
LobbyManager::LobbyManager(QObject *parent, QQmlContext * context, QString username, bool use_NSD) :
    QObject(parent), mServer(new TCPServer(this)), mGameLobby(0)
{
    mUserName = (username == "" ?  QHostInfo::localHostName():username); // or username if not an empty stringm
    qDebug() << mUserName;
    mContext = context;
    mConnectedString = " connected to VaporChat Main Lobby.";
    if(use_NSD) // if system should use nsd
    {
        connect(&mLANPeerManager,SIGNAL(recordsChanged()),this,SLOT(lanUsersUpdated()));
        connect(&mLANPeerManager,SIGNAL(resolvedRecord(QHostInfo,int)),this,SLOT(userRecordResolved(QHostInfo,int)));
        connect(&mLANGameManager,SIGNAL(recordsChanged()),this,SLOT(lanLobbysUpdated()));
        connect(&mLANGameManager,SIGNAL(resolvedRecord(QHostInfo,int)),this,SLOT(gameLobbyResolved(QHostInfo,int)));


        mLANPeerManager.setLocalName(mUserName+ "$$" + QHostInfo::localHostName());
        mLANPeerManager.registerService("Vapor Arcade Chat","_vaporarcade_peer._tcp",mServer->serverPort());
        mLANPeerManager.browseService("_vaporarcade_peer._tcp");
        mLANGameManager.browseService("_vaporarcade_gl._tcp");
        mUserList.append(mUserName);

    }
    mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
    mContext->setContextProperty("NSDGameLobbyList",QVariant::fromValue(mGameLobbyList));
    mContext->setContextProperty("LobbyManager",this);
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
    foreach(NetworkUser * nusr, mLANUsers)
    {
        if(nusr->getName() == user)
            return true;
    }

    return false;
}


ChatConnection * LobbyManager::alreadyWasConnected(ChatConnection *connection)
{
    ChatConnection* ret_val(0);
    foreach( NetworkUser * user, mLANUsers)
    {
        if(user->getConnection()->getHostInfo().hostName() == connection->getHostInfo().hostName())
        {
           user->setConnection(connection);
           ret_val = user->getConnection();
           break;
        }
    }
    return ret_val;
}

void LobbyManager::connectToQML(QQuickItem * root)
{
    mNetLobby = root->findChild<QQuickItem *>("NetLobby");
    newMessage(("<E> " + QString::number(mUserName.size()) + ' ' + mUserName + TerminationToken), ChatConnection::HelloLobby);
}

QStringList LobbyManager::findUsersThatLeft(const QStringList &records)
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
            QByteArray message = usr->getName().toUtf8();
            message.append(TerminationToken);
            QByteArray message_w_header = "<G > " + QByteArray::number(message.size()) + ' ' + message;
            qDebug() << message_w_header;
            emit newMessage(message_w_header, ChatConnection::GoodByeLobby);
            users_removed = true;
            usr->deleteLater();
        }
    }
    if(users_removed)
        mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
    return records_to_users;
}


void LobbyManager::createGameLobby( QString lobbyname)
{
    mLANGameManager.setLocalName(lobbyname);
    mLANGameManager.registerService((lobbyname + "$$" + mUserName),"_vaporarcade_gl._tcp",mServer->serverPort());
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

    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(connectionError(QAbstractSocket::SocketError)));
    connect(connection,SIGNAL(newMessage(QString,int)),this,SLOT(newMessage(QString,int)));
    connect(connection, SIGNAL(userDisconnected()), this, SLOT(disconnected()));
    if(!alreadyWasConnected(connection))
    {
//        QString username = connection->getHostInfo().hostName();
//        NetworkUser * netuser = new NetworkUser(this,username,connection);
//        mLANUsers.append(netuser);
    }
}

void LobbyManager::newMessage(QString message, int type)
{
    QVariant returnedValue;
    switch(type)
    {
        case ChatConnection::HelloLobby:
        {
            int last_space_i(message.lastIndexOf(' '));
            message.chop(1);
            QString username(message.mid(last_space_i));
            username.remove(' ');
            qDebug() << username;
            if(!awareOfUserAlready(username))
            {
                mUserList.append(username);
                mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
            }
            QMetaObject::invokeMethod(mNetLobby, "submitMessage",
                                      Q_RETURN_ARG(QVariant, returnedValue),
                                      Q_ARG(QVariant, QVariant(username + ' ' + mConnectedString)));
            break;
        }
        case ChatConnection::GoodByeLobby:
        {
            int last_space_i(message.lastIndexOf(' '));
            message.chop(1);
            QString username(message.mid(last_space_i));
            username.remove(' ');
            mUserList.removeOne(username);
            mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
            QMetaObject::invokeMethod(mNetLobby, "submitMessage",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                      Q_ARG(QVariant, QVariant(username + " disconnected from VaporChat Main Lobby.")));
            break;
        }
        default:{break;}
    }
}

void LobbyManager::disconnected()
{
    if (ChatConnection *connection = qobject_cast<ChatConnection *>(sender()))
        removeConnection(connection);

}

void LobbyManager::connectionError(QAbstractSocket::SocketError /* socketError */)
{
    if (ChatConnection *connection = qobject_cast<ChatConnection *>(sender()))
        removeConnection(connection);
}

void LobbyManager::lanLobbysUpdated()
{
    QStringList records = mLANGameManager.getServiceNames();
}

void LobbyManager::lanUsersUpdated()
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



void LobbyManager::removeConnection(ChatConnection *connection)
{
   foreach(NetworkUser * user, mLANUsers)
   {
       if(user->getConnection() == connection)
       {
           connection->close();
       }
   }

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
}


QString LobbyManager::serviceNameToUsername(QString hostname)
{
    QString username(hostname);
    username = username.split("$$")[0];
    return username;
}


void LobbyManager::userRecordResolved(QHostInfo info, int port)
{
    QString user(mCurrentRecordsResolving.first());
    mCurrentRecordsResolving.pop_front();
    QString username = user;
    user+=  '$'+info.hostName();
    qDebug() << username;
    qDebug() << user;
    if(username != mUserName && info.addresses()[0] != mServer->serverAddress())
    {
        QHostAddress addr(info.addresses()[0]);
        ChatConnection* ccon = new ChatConnection(this,user,info,port);
        NetworkUser * netuser = new NetworkUser(this,username,ccon);
        if(!awareOfUserAlready(username))
        {
            mUserList.append(username);
            mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
        }
        mLANUsers.append(netuser);

        ccon->connectToHost(addr, port);
    }
    if(mCurrentRecordsResolving.length() > 0)
        mLANPeerManager.resolveSercviceWithTypeAndNameContains(mCurrentRecordsResolving.first(),"_vaporarcade_peer._tcp.");

}

LobbyManager::~LobbyManager()
{
    if(mServer)
        delete mServer;
    for(int i = 0; i < mLANUsers.length(); i++)
    {
        NetworkUser * user = mLANUsers[i];
        user->deleteLater();
    }
    delete mGameLobby;
    delete mMainLobby;
}
