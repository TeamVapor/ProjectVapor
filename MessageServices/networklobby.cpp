#include "networklobby.h"
#include "networkuser.h"
#include <QHostAddress>
NetworkLobby::NetworkLobby(QObject *parent, QString name, int type) :
    iLobby(parent)
{
    mName = name;
    mLobbyType = type;
}



void NetworkLobby::addUser(iUser *user)
{
    if(!hasUser(user))
        mLobbyUsers.append(user);
}

void NetworkLobby::anounceUserAdded()
{

}

void NetworkLobby::anounceUserRemoved(QString exit_verb)
{

}

void NetworkLobby::removeUser(iUser *user)
{
    if(!hasUser(user))
        mLobbyUsers.removeAll(user);
}

QString NetworkLobby::getLobbyName()
{
    return mName;
}


int NetworkLobby::getLobbyType()
{
    return mLobbyType;
}

int NetworkLobby::getUserCount()
{
    return mLobbyUsers.count();
}

QList<iUser *> NetworkLobby::getUsers()
{
    return mLobbyUsers;
}


bool NetworkLobby::hasUser(iUser *user)
{
    foreach(iUser * usr, mLobbyUsers )
    {
        if(usr->getName().compare(user->getName()) == 0)
            if(usr == user)
                return true;
    }
    return false;
}


void NetworkLobby::sendMessage(QString message)
{
    foreach(iUser * usr, mLobbyUsers)
    {
        usr->sendMessage(message);
    }
}


void NetworkLobby::setName(QString name)
{
    mName = name;
}

NetworkLobby::~NetworkLobby()
{
    mLobbyUsers.clear();
}
