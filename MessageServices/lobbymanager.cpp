#include "lobbymanager.h"
#include "tcpserver.h"
LobbyManager::LobbyManager(QObject *parent, QString username, bool use_NSD) :
    QObject(parent), mServer(new TCPServer(this))
{
    if(use_NSD)
    {
        connect(&mLANPeerManager,SIGNAL(recordsChanged()),this,SLOT(userRecordsChanged()));
        connect(&mLANGameManager,SIGNAL(resolvedRecord(QHostInfo,int)),this,SLOT(resolvedRecord(QHostInfo,int)));
        connect(&mLANGameManager,SIGNAL(recordsChanged()),this,SLOT(gameRecordsChanged()));

        mLANPeerManager.setLocalName(mUserName);
        mLANPeerManager.registerService("Vapor Arcade Chat","_vaporarcade_peer._tcp",0);
        mLANPeerManager.browseService("_vaporarcade_peer._tcp");
        mLANGameManager.browseService("_vaporarcade_gamelobby._tcp");

    }
    connect(mServer,SIGNAL(newChatConnection(ChatConnection*)),this,SLOT(newConnection(ChatConnection*)));
}

void LobbyManager::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    //QList<ChatConnection *> connections = peers.values();
    //foreach (ChatConnection *connection, connections)
    //    connection->sendMessage(message);
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
  //  if (ChatConnection *connection = qobject_cast<ChatConnection *>(sender()))
   //     removeConnection(connection);
}

void LobbyManager::connectionError(QAbstractSocket::SocketError /* socketError */)
{
   // if (ChatConnection *connection = qobject_cast<ChatConnection *>(sender()))
   //     removeConnection(connection);
}

void LobbyManager::removeConnection(ChatConnection *connection)
{
   // if (peers.contains(connection->peerAddress())) {
   //     peers.remove(connection->peerAddress());
   //     QString nick = connection->name();
   //     if (!nick.isEmpty())
  //          emit participantLeft(nick);
   // }
  //  connection->deleteLater();
}

LobbyManager::~LobbyManager()
{
    if(mServer)
        delete mServer;
}
