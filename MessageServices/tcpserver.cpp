#include "tcpserver.h"
#include "chatconnection.h"

TCPServer::TCPServer(QObject *parent) :
    QTcpServer(parent)
{
    listen();
}

void TCPServer::incomingConnection(qintptr handle)
{
    ChatConnection *connection = new ChatConnection(this);
    connection->setSocketDescriptor(handle);
    emit newChatConnection(connection);
}
