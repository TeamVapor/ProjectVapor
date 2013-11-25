#ifndef NETWORKUSER_H
#define NETWORKUSER_H

class NetworkLobby;

#include "iuser.h"
class ChatConnection;
#include <QHostInfo>
class NetworkUser : public iUser
{
    Q_OBJECT
public:
    NetworkUser(QObject *parent = 0, QString name = "", QHostInfo info =  QHostInfo(), int port = 0);
    QHostAddress getAddress();
    void sendMessage(QString message);
    int getPort();
    ChatConnection * getConnection();
signals:


public slots:
    void setPort(int port);
    void setConnection( ChatConnection * connection);
protected:
    ChatConnection * mConnection;
    QHostInfo        mHostInfo;
    int              mPort;

};

#endif // NETWORKUSER_H
