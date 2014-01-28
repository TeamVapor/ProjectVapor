#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "Network/Chat/chatconnection.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = 0);

signals:
    void newChatConnection(ChatConnection * connection);
public slots:

protected:
    void incomingConnection(qintptr handle);

};

#endif // TCPSERVER_H
