#include "peermanager.h"
#include <QStringList>
PeerManager::PeerManager(QObject *parent) :
    QObject(parent)
{
}


/*QStringList PeerManager::findUsersThatLeft(const QStringList &records)
{
    QStringList records_to_users;
    bool users_removed(false);
    foreach(QString record, records)
    {
        records_to_users.append(serviceNameToUsername(record));
    }

    /*foreach( QString rec_res, mCurrentRecordsResolving)
    {
        if(!records_to_users.contains(rec_res))
        {
            mCurrentRecordsResolving.removeOne(rec_res);
        }
    }
    foreach( NetworkUser * usr, mLANUsers)
    {
        qDebug() << usr->getName();
        if(!records_to_users.contains(usr->getName()))
        {

            mUserList.removeOne(QVariant(usr->getName()));
            if(!mLANUsers.removeOne(usr))
                qDebug() << "failed to remove user";
            qDebug() << usr->getName();
            QByteArray message = usr->getName().toUtf8();
            message.append(TerminationToken);
            QByteArray message_w_header = "<G > " + QByteArray::number(message.size()) + ' ' + message;
            qDebug() << message_w_header;
            emit newMessage(message_w_header, ChatConnection::GoodByeLobby);
            users_removed = true;
            usr->deleteLater();
        }
    }
    if(users_removed)
        mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
    return records_to_users;
}*/


QString PeerManager::nickName() const
{
    //return QString(peerManager->userName()) + '@' + QHostInfo::localHostName()
        //   + ':' + QString::number(server.serverPort());
    return mUserName;
}

void PeerManager::lanUsersUpdated()
{
   /* findUsersThatLeft(records);
    QString username;
    foreach(QString record,records)
    {
        username = (serviceNameToUsername(record));
        if(!awareOfUserAlready(username))
        {
            mCurrentRecordsResolving.append(username);
        }
    }
    if(mCurrentRecordsResolving.length() > 0)
    {
        // only use if demanding immediate stop
        //mLANPeerManager.forceStopResolving();
        mLANPeerManager.resolveServciceByType("_vaporarcade_peer._tcp.",records.first());
    }*/
}

void PeerManager::resolveTimedOutUser()
{

}


QString PeerManager::serviceNameToUsername(QString hostname)
{
    QString username(hostname);
    username = username.split("$$")[0];
    return username;
}


void PeerManager::userRecordResolved(QHostInfo info, int port)
{
   /* QString user(mCurrentRecordsResolving.first());
    mCurrentRecordsResolving.pop_front();
    QString username = user;
    user+=  '$'+info.hostName();
    qDebug() << username;
    qDebug() << user;
    if(username != mUserName && info.addresses()[0] != mServer->serverAddress())
    {
        QHostAddress addr(info.addresses()[0]);
        ChatConnection* ccon = new ChatConnection(this,user,info,port);
        NetworkUser * netuser = new NetworkUser(this,username,ccon);
        if(!awareOfUserAlready(username))
        {
            mUserList.append(username);
            mContext->setContextProperty("NSDUserList",QVariant::fromValue(mUserList));
        }
        mLANUsers.append(netuser);

        ccon->connectToHost(addr, port);
    }
    if(mCurrentRecordsResolving.length() > 0)
        mLANPeerManager.resolveSercviceWithTypeAndNameContains(mCurrentRecordsResolving.first(),"_vaporarcade_peer._tcp.");
*/
}

