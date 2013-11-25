#ifndef ILOBBY_H
#define ILOBBY_H

#include <QObject>

class iUser;
class iLobby : public QObject
{
    Q_OBJECT
public:

    virtual void sendMessage(QString message) = 0;
    virtual QString getLobbyName() = 0;
    virtual int getLobbyType() = 0;
    virtual int getUserCount() = 0;
    virtual QList<iUser *> getUsers() = 0;
    virtual bool hasUser(iUser * user) = 0;

signals:
    void sentMessageSuccess();
    void failedToSendMessage();

public slots:
    virtual void addUser(iUser * user) = 0;
    virtual void removeUser(iUser * user) = 0;

protected:

    // Lobby Members
    QString        mName;
    QList<iUser *> mLobbyUsers;
    int            mLobbyType;
    QByteArray     mChatLog;


    explicit iLobby(QObject *parent = 0){ Q_UNUSED(parent)}
    ~iLobby()
    {
        mName = "";
        mLobbyType = 0;
        mLobbyUsers.clear();
        mChatLog.clear();
    }
    virtual void anounceUserAdded() = 0;
    virtual void anounceUserRemoved(QString exit_verb) = 0;
};

#endif // ILOBBY_H
