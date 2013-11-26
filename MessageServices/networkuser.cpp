#include "networkuser.h"
#include "networklobby.h"
#include "chatconnection.h"
#include <QHostInfo>
#include <QHostAddress>
NetworkUser::NetworkUser(QObject *parent, QString name, ChatConnection * connection) :
    iUser(parent,name), mConnection(connection)
{

}



// getters and setters //
QHostAddress NetworkUser::getAddress()
{
    return mConnection->getHostAddress();
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

