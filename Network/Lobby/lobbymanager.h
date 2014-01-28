#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H

#include <QObject>
#include "Network/Services/qnsdmanager.h"
class NetworkUser;
class QQmlContext;
class NetworkLobby;
class QQuickItem;
class iLobby;

class LobbyManager : public QObject
{
    Q_OBJECT
public:
    explicit LobbyManager(QObject *parent = 0);
    ~LobbyManager();

/************************************************************************
*Declare QML Interface methods
*
*
************************************************************************/
Q_INVOKABLE void createGameLobby(QString lobbyname);

signals:

    void participantLeft(const QString &nick);
    void lobbyCreated(const QString & lobbyname, const QString & host);
    void lobbyClosed(const QString & lobbyname, const QString & host);

private slots:
    void gameLobbyResolved(QHostInfo info, int port);

private:

protected:
    QString            mConnectedString;
    QVariantList       mGameLobbyList;
    QList<iLobby *>    mLobbies;
    //QNSDManager             mLANGameManager;
    //NetworkLobby *          mGameLobby;
    //NetworkLobby *          mMainLobby;
    //QQmlContext  *          mContext;

};

#endif // LOBBYMANAGER_H
