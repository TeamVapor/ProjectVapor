#ifndef NETWORKUSER_H
#define NETWORKUSER_H

class NetworkLobby;

#include "iuser.h"
class QHostInfo;
class QHostAddress;
class ChatConnection;
class NetworkUser : public iUser
{
    Q_OBJECT
public:
    NetworkUser(QObject *parent = 0, QString name = "", ChatConnection *connection = 0);
    QHostAddress getAddress();
    QHostInfo    getHostInfo();
    int          getPort();
    void sendMessage(QString message);
    ChatConnection * getConnection();
signals:


public slots:

    void setConnection( ChatConnection * connection);
protected:
    ChatConnection * mConnection;


};

#endif // NETWORKUSER_H
