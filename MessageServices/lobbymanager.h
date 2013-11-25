#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H

#include <QObject>
#include "Bonjour/qnsdmanager.h"
class NetworkUser;
class QQmlContext;
class NetworkLobby;
#include "tcpserver.h";
#include "chatconnection.h"
class LobbyManager : public QObject
{
    Q_OBJECT
public:
    explicit LobbyManager(QObject *parent = 0, QQmlContext * context = 0, QString username = "", bool use_NSD = true);
    ~LobbyManager();

    void sendMessage(const QString &message);
    QString nickName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

signals:
    void newMessage(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void lobbyCreated(const QString & lobbyname, const QString & host);
    void lobbyClosed(const QString & lobbyname, const QString & host);

private slots:
    void newConnection(ChatConnection *connection);
    void connectionError(QAbstractSocket::SocketError socketError);
    void lanUsersUpdated();
    void lanLobbysUpdated();
    void userRecordResolved(QHostInfo info, int port);
    void gameLobbyResolved(QHostInfo info, int port);
    void resolveTimedOutUser();
    void resolveTimedOutLobby();
    void disconnected();
    void readyForUse();

private:
    bool awareOfUserAlready(QString user);
    void findUsersThatLeft(const QStringList &records);
    void removeConnection(ChatConnection *connection);
    QString serviceNameToUsername(QString hostname);

protected:
    QNSDManager             mLANPeerManager;
    QNSDManager             mLANGameManager;
    QString                 mUserName;
    QVariantList            mUserList;
    QVariantList            mGameLobbyList;
    QList <QString>         mCurrentRecordsResolving;
    QList<NetworkUser *>    mLANUsers;
    NetworkLobby *          mGameLobby;
    NetworkLobby *          mMainLobby;
    TCPServer    *          mServer;
    QQmlContext  *          mContext;

};

#endif // LOBBYMANAGER_H
