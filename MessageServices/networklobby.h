#ifndef NETWORKLOBBY_H
#define NETWORKLOBBY_H

class QHostAddress;
#include "ilobby.h"
class NetworkLobby : public iLobby
{
    Q_OBJECT
public:
    explicit NetworkLobby(QObject *parent = 0, QString name = "", int type = 0);
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


};

#endif // NETWORKLOBBY_H
