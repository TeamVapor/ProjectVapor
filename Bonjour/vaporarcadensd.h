#ifndef VAPORARCADENSD_H
#define VAPORARCADENSD_H

#include <QObject>
#include "Bonjour/qnsdmanager.h"
class QQmlContext;
class VaporArcadeNSD : public QObject
{
    Q_OBJECT
public:
    explicit VaporArcadeNSD(QObject *parent = 0, QString Username = "");
    void setContext(QQmlContext * context);
    QMultiHash<QPair<QHostAddress,int>,QString>  getRecordAdresses();
    void resolveRecords();
signals:
    void userListChanged();

public slots:
    void beginBrowsingUsers();
    void beginBrowsingLobbies();
    void userRecordsChanged();
    void gameRecordsChanged();
    void resolvedRecord(QHostInfo hostinfo,int port);
    void startGameLobby(QString lobbyname);
    
private:
    QNSDManager    mChatBrowser;
    QNSDManager    mGameBrowser;
    QMultiHash<QPair<QHostAddress,int>,QString>  mAddressList;
    int            mCurrentRecord;
    QVariantList   mUserList;
    QVariantList   mGameLobbyList;
    QQmlContext    *mContext;
};

#endif // VAPORARCADENSD_H
