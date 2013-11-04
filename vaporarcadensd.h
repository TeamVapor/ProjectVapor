#ifndef VAPORARCADENSD_H
#define VAPORARCADENSD_H

#include <QObject>
#include "qnsdmanager.h"
class QQmlContext;
class VaporArcadeNSD : public QObject
{
    Q_OBJECT
public:
    explicit VaporArcadeNSD(QObject *parent = 0);
    void setContext(QQmlContext * context);

signals:


public slots:
    void beginBrowsingUsers();
    void beginBrowsingLobbies();
    void userRecordsChanged();
    void gameRecordsChanged();
    void startGameLobby(QString lobbyname);

private:
    QNSDManager    mChatBrowser;
    QNSDManager    mGameBrowser;
    QVariantList   mUserList;
    QVariantList   mGameLobbyList;
    QQmlContext    *mContext;
};

#endif // VAPORARCADENSD_H
