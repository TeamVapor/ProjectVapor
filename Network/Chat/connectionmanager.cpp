#include "connectionmanager.h"
#include "Network/Chat/chatconnection.h"
ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent)
{
}



ChatConnection *ConnectionManager::alreadyWasConnected(ChatConnection *connection)
{
    ChatConnection* ret_val(0);
    foreach( ChatConnection * prevconnect, mConnections)
    {
        if(prevconnect->getAddress() == connection->getAddress() &&
           prevconnect->getAddress() == connection->getReceiversName())
        {
           ret_val = prevconnect;
           break;
        }
    }
    return ret_val;
}



void ConnectionManager::disconnected()
{
    if (ChatConnection *connection = qobject_cast<ChatConnection *>(sender()))
        removeConnection(connection);

}

bool ConnectionManager::hasConnection(const QHostAddress &senderIp, int senderPort) const
{
    QString compare_ip(senderIp.toString());
    if (senderPort == -1)
    {
        foreach(iChatConnection * connection, mConnections)
        {
            if(connection->getAddress() == compare_ip)
            {
                return true;
            }
        }
    }
    else
    {
        foreach(iChatConnection * connection, mConnections)
        {
            if(connection->getAddress() == compare_ip)
            {
                if(connection->getPort() == senderPort)
                    return true;
            }
        }
    }
    return false;
}

void ConnectionManager::newConnection(ChatConnection *connection)
{
    if(!alreadyWasConnected(connection))
    {
        connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(connectionError(QAbstractSocket::SocketError)));
        connect(connection,SIGNAL(newMessage(QString,int,ChatConnection*const)),this,SLOT(newMessage(QString,int,ChatConnection*const)));
        connect(connection, SIGNAL(userDisconnected()), this, SLOT(disconnected()));
        mConnections.append(connection);
        QString username = connection->getReceiversName();
       // NetworkUser * netuser = new NetworkUser(this,username,connection);
       // mLANUsers.append(netuser);
    }
}


void ConnectionManager::newMessage(QString message, int type, ChatConnection * const connection)
{

    /*QVariant returnedValue;
    switch(type)
    {
        case ChatConnection::HelloLobby:
        {
            int last_space_i(message.lastIndexOf(' '));
            message.chop(1);
            QString username(message.mid(last_space_i));
            username.remove(' ');
            qDebug() << username;
            if(!awareOfUserAlready(username))
            {
                mUserList.append(username);
                mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
            }
            QMetaObject::invokeMethod(mNetLobby, "submitMessage",
                                      Q_RETURN_ARG(QVariant, returnedValue),
                                      Q_ARG(QVariant, QVariant(username + ' ' + mConnectedString)));
            break;
        }
        case ChatConnection::GoodByeLobby:
        {
            int last_space_i(message.lastIndexOf(' '));
            message.chop(1);
            QString username(message.mid(last_space_i));
            username.remove(' ');
            mUserList.removeOne(username);
            mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
            QMetaObject::invokeMethod(mNetLobby, "submitMessage",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                      Q_ARG(QVariant, QVariant(username + " disconnected from VaporChat Main Lobby.")));
            break;
        }
        case ChatConnection::LobbyMessage:
        {
            int last_space_i(message.lastIndexOf(' '));
            message.chop(1);
            QString username(message.mid(last_space_i));
            QMetaObject::invokeMethod(mNetLobby, "submitMessage",
                          Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, QVariant(message)));
            break;
        }
        default:{break;}
    }*/
}

void ConnectionManager::removeConnection(ChatConnection *connection)
{
   foreach(ChatConnection * comp_con, mConnections)
   {
       if(comp_con->getAddress() == connection->getAddress())
       {
           qDebug() << "Removing connection to " << connection->getReceiversName();
           if(!mConnections.removeAll(comp_con))
           {
                qDebug() << "failed to remove connection to " << connection->getReceiversName();
                connection->close();
           }
       }
   }

}
