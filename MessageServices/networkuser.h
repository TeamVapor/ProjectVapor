#ifndef NETWORKUSER_H
#define NETWORKUSER_H

#include "iuser.h"
class NetworkLobby;
class QHostAddress;
#include "chatconnection.h"
class NetworkUser : public iUser
{
    Q_OBJECT
public:
    explicit NetworkUser(QObject *parent = 0, QString name = "", QHostAddress addr =  QHostAddress(), int port = 0);
    QHostAddress getAddress();
    void sendMessage(QString message);
    int getPort();
    ChatConnection * getConnection();
signals:


public slots:
    void setPort(int port);
    void setAddress(QHostAddress addr);
    void setConnection( ChatConnection * connection);
protected:
    ChatConnection * mConnection;
    QHostAddress     mAddress;
    int              mPort;

};

#endif // NETWORKUSER_H
