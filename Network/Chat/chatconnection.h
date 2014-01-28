#ifndef CHATCONNECTION_H
#define CHATCONNECTION_H

#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QHostInfo>
#include <QHostAddress>
static const int MaxBufferSize = 1024000;
#include "Network/Interfaces/ichatconnection.h"
class ChatConnection : public QTcpSocket, public iChatConnection
{
    Q_OBJECT
    Q_INTERFACES(iChatConnection)
public:
    enum ConnectionState {
        WaitingForPingReply,
        WaitingForInviteReply,
        WaitingForRequestReply,
        WaitingForLobbyEntered,
        ReadingInviteReply,
        ReadingPingReply,
        ReadingRequestReply,
        ReadingEnteredLobby,
        ReadyForUse
    };
    enum DataType {
        LobbyMessage,
        GameInvite,
        InviteDecline,
        InviteAccept,
        VaporPing,
        VaporPong,
        HelloLobby,
        GoodByeLobby,
        Undefined
    };

    ChatConnection(QObject *parent = 0, QString hostname = "", QHostInfo info = QHostInfo(), int portnum = 0);
    ~ChatConnection();
    void setHostName(QString name){mHostName = name;}
    QHostInfo getHostInfo();
    QHostAddress getHostAddress();
    int getPort();
    void setConnectionEstablishedMessage(QString message);

    QString getAddress();
    QString getReceiversName();
    bool connectedToUser(iUser * user);
    void sendMessage(QString message);

public slots:
    void sendPing();

signals:
    void readyForUse();
    void newMessage(QString message, int type);
    void userDisconnected();
    void sentMessageSuccessfully();
    void failedToSendMessage();
    void anounceUserConnected();
    void anounceConnectionLost();

protected:
    void timerEvent(QTimerEvent *timerEvent);

private slots:
    void processReadyRead();

    void sendConnectionEstablished();

    //void sendGameInvite(QString gamename, QString gamesystem, QString target_user);
    void socketDisconnected();

private:
    int readDataIntoBuffer(int maxSize = MaxBufferSize);
    int dataLengthForCurrentDataType();
    bool readProtocolHeader();
    bool hasEnoughData();
    void processData();

    QString         mHostName;
    QHostInfo       mHostInfo;
    int             mPort;
    QTimer          mPingTimer;
    QTime           mPongTime;
    QByteArray      mBuffer;
    ConnectionState mConnectState;
    DataType        mCurrentType;
    int             mCurrentTypeByteCount;
    int             mTimerID;
};

#endif // CHATCONNECTION_H

