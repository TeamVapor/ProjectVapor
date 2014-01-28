#ifndef NETWORKUSER_H
#define NETWORKUSER_H

class NetworkLobby;

#include "Network/Interfaces/iuser.h"
class QHostInfo;
class QHostAddress;
class ChatConnection;
class NetworkUser : public iUser
{
    Q_OBJECT
public:
    NetworkUser(QObject *parent = 0, QString name = "", ChatConnection *connection = 0);
    QString      getAddress();
    QHostInfo    getHostInfo();
    int          getPort();
    ChatConnection * getConnection();
signals:


public slots:
    void sendMessage(QString message);
    void setConnection( ChatConnection * connection);
protected:
    ChatConnection * mConnection;


};

#endif // NETWORKUSER_H
