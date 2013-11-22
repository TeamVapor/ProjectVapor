#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H

#include <QObject>
#include "Bonjour/qnsdmanager.h"
class NetworkUser;
#include "tcpserver.h";
class ChatConnection;
#include "networklobby.h"
class LobbyManager : public QObject
{
    Q_OBJECT
public:
    explicit LobbyManager(QObject *parent = 0, QString username = "", bool use_NSD = true);
    ~LobbyManager();

    void sendMessage(const QString &message);
    QString nickName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

signals:
    void newMessage(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

private slots:
    void newConnection(ChatConnection *connection);
    void connectionError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void readyForUse();

private:
    void removeConnection(ChatConnection *connection);


protected:
    QNSDManager             mLANPeerManager;
    QNSDManager             mLANGameManager;
    QString                 mUserName;
    //int            mCurrentRecord;
    QVariantList            mUserList;
    QVariantList            mGameLobbyList;
    QList<NetworkUser *>    mLANUsers;
    NetworkLobby *          mGameLobby;
    NetworkLobby *          mMainLobby;
    TCPServer    *          mServer;


};

#endif // LOBBYMANAGER_H
