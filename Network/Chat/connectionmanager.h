#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "Network/Chat/tcpserver.h"
//#include "Network/Interfaces/ichatconnection.h"
#include <QObject>
class ChatConnection;
class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = 0);
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;
signals:

private:
   ChatConnection * alreadyWasConnected(ChatConnection * connection);
   void removeConnection(ChatConnection *connection);

public slots:
   //void connectionError(QAbstractSocket::SocketError socketError);
   void newConnection(ChatConnection *connection);
   void newMessage(QString message, int type, ChatConnection*const connection);
protected slots:
   void disconnected();
protected:
    QList<ChatConnection *>   mConnections;
};

#endif // CONNECTIONMANAGER_H
