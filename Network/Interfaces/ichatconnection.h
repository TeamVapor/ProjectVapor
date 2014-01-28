#ifndef ICHATCONNECTION_H
#define ICHATCONNECTION_H


#include <QObject>

class iUser;
class iChatConnection
{

public:
    virtual QString getAddress() = 0;
    virtual QString getReceiversName() = 0;
    virtual int     getPort() = 0;
    virtual bool connectedToUser(iUser * user) = 0;
    virtual void sendMessage(QString message) = 0;
protected:
    explicit iChatConnection(QObject *parent = 0){ Q_UNUSED(parent)}

};
Q_DECLARE_INTERFACE(
        iChatConnection,
        "com.Network.Chat.iChatConnection/1.0")

#endif // ICHATCONNECTION_H

