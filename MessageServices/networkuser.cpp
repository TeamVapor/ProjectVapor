#include "networkuser.h"
#include "networklobby.h"
#include "chatconnection.h"
#include <QHostInfo>
NetworkUser::NetworkUser(QObject *parent, QString name, QHostInfo info, int port) :
    iUser(parent)
{
    mHostInfo = info;
    mPort = port;
    mConnection = new ChatConnection(this, name);
}



// getters and setters //
QHostAddress NetworkUser::getAddress()
{
    return mHostInfo.addresses()[0];
}


ChatConnection * NetworkUser::getConnection()
{
    return mConnection;
}

int NetworkUser::getPort()
{
    return mPort;
}

void NetworkUser::setConnection(ChatConnection *connection)
{
    mConnection = connection;
}


void NetworkUser::setPort(int port)
{
    mPort = port;
}



void NetworkUser::sendMessage(QString message)
{
    mConnection->sendMessage(message);
}

