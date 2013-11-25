#ifndef NETWORKLOBBY_H
#define NETWORKLOBBY_H


#include "ilobby.h"
class QHostAddress;
class NetworkLobby : public iLobby
{
    Q_OBJECT
public:
    NetworkLobby(QObject *parent = 0, QString name = "", int type = 0);
    ~NetworkLobby();
    void sendMessage(QString message);
    QString getLobbyName();
    int getLobbyType();
    int getUserCount();
    QList<iUser *> getUsers();
    bool hasUser(iUser *user);

signals:

public slots:
    void addUser(iUser * user);
    void removeUser(iUser * user);
    void setName(QString name);


protected:
    void anounceUserAdded();
    void anounceUserRemoved(QString exit_verb);

};

#endif // NETWORKLOBBY_H
