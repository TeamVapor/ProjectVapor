#ifndef VAPORARCADENSD_H
#define VAPORARCADENSD_H

#include <QObject>
#include "Network/Services/qnsdmanager.h"
class NetworkUser;
class QQmlContext;
class NetworkLobby;
class QQuickItem;
class VaporArcadeNSD : public QObject
{
    Q_OBJECT
public:
    explicit VaporArcadeNSD(QObject *parent = 0, QQmlContext * context = 0, QString username = "", bool use_NSD = true);
    ~VaporArcadeNSD();


    QString nickName() const;
    void connectToQML(QQuickItem * root);



/************************************************************************
*Declare QML Interface methods
*
*
************************************************************************/
Q_INVOKABLE void createGameLobby(QString lobbyname);

signals:

    void participantLeft(const QString &nick);
    void lobbyCreated(const QString & lobbyname, const QString & host);
    void newUserConnected(QString message);
    void lobbyClosed(const QString & lobbyname, const QString & host);

private slots:
    void lanUsersUpdated();
    void lanLobbysUpdated();
    void userRecordResolved(QHostInfo info, int port);
    void gameLobbyResolved(QHostInfo info, int port);
    void resolveTimedOutUser();
    void resolveTimedOutLobby();

private:
    bool awareOfUserAlready(QString user);
    QStringList findUsersThatLeft(const QStringList &records);
    QString serviceNameToUsername(QString hostname);

protected:
    QNSDManager             mLANPeerManager;
    int                     mChatPortNum;
   // QNSDManager             mLANGameManager;
    QString                 mUserName;
  //  QString                 mConnectedString;
    QVariantList            mUserList;
 //   QVariantList            mGameLobbyList;
    QList <QString>         mCurrentRecordsResolving;
    QList<NetworkUser *>    mLANUsers;
 //   NetworkLobby *          mGameLobby;
  //  NetworkLobby *          mMainLobby;
    QQmlContext  *          mContext;

};

#endif // VAPORARCADENSD_H
