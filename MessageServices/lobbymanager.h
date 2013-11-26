#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H

#include <QObject>
#include "Bonjour/qnsdmanager.h"
class NetworkUser;
class QQmlContext;
class NetworkLobby;
class QQuickItem;
#include "tcpserver.h"
#include "chatconnection.h"
class LobbyManager : public QObject
{
    Q_OBJECT
public:
    explicit LobbyManager(QObject *parent = 0, QQmlContext * context = 0, QString username = "", bool use_NSD = true);
    ~LobbyManager();


    QString nickName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;
    void connectToQML(QQuickItem * root);



/************************************************************************
*Declare QML Interface methods
*
*
************************************************************************/
Q_INVOKABLE void createGameLobby(QString lobbyname);
Q_INVOKABLE void sendMessage(QString message);

signals:

    void participantLeft(const QString &nick);
    void lobbyCreated(const QString & lobbyname, const QString & host);
    void newUserConnected(QString message);
    void lobbyClosed(const QString & lobbyname, const QString & host);

private slots:
    void newConnection(ChatConnection *connection);
    void connectionError(QAbstractSocket::SocketError socketError);
    void lanUsersUpdated();
    void lanLobbysUpdated();
    void newMessage(QString message, int type);
    void userRecordResolved(QHostInfo info, int port);
    void gameLobbyResolved(QHostInfo info, int port);
    void resolveTimedOutUser();
    void resolveTimedOutLobby();
    void disconnected();

private:
    bool awareOfUserAlready(QString user);
    ChatConnection * alreadyWasConnected(ChatConnection * connection);
    QStringList findUsersThatLeft(const QStringList &records);
    void removeConnection(ChatConnection *connection);
    QString serviceNameToUsername(QString hostname);

protected:
    QNSDManager             mLANPeerManager;
    QNSDManager             mLANGameManager;
    QString                 mUserName;
    QString                 mConnectedString;
    QQuickItem   *          mNetLobby;
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
