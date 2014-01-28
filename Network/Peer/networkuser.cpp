#include "Network/Peer/networkuser.h"
#include "Network/Lobby/networklobby.h"
#include "Network/Chat/chatconnection.h"
#include <QHostInfo>
#include <QHostAddress>
NetworkUser::NetworkUser(QObject *parent, QString name, ChatConnection * connection) :
    iUser(parent,name), mConnection(connection)
{

}



// getters and setters //
QString NetworkUser::getAddress()
{
    return mConnection->getHostAddress().toString();
}


ChatConnection * NetworkUser::getConnection()
{
    return mConnection;
}

int NetworkUser::getPort()
{
    return mConnection->getPort();
}

void NetworkUser::setConnection(ChatConnection *connection)
{
    if(mConnection)
        delete mConnection;
    mConnection = connection;
}


void NetworkUser::sendMessage(QString message)
{
    mConnection->sendMessage(message);
}


