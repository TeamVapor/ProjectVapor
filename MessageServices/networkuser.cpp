#include "networkuser.h"
#include "networklobby.h"

NetworkUser::NetworkUser(QObject *parent, QString name, QHostAddress addr, int port) :
    iUser(parent)
{
    mAddress = addr;
    mPort = port;
}



// getters and setters //
QHostAddress NetworkUser::getAddress()
{
    return mAddress;
}


ChatConnection * NetworkUser::getConnection()
{
    return mConnection;
}

int NetworkUser::getPort()
{
    return mPort;
}

void NetworkUser::setAddress(QHostAddress addr)
{
    mAddress = addr;
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

}
