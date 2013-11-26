#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QHostInfo>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>

static const int MaxBufferSize = 1024000;

class ChatConnection : public QTcpSocket
{
    Q_OBJECT

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
    QString name();
    void setHostName(QString name){mHostName = name;}
    QHostInfo getHostInfo();
    QHostAddress getHostAddress();
    int getPort();
    bool sendMessage(const QString &message);
    void setConnectionEstablishedMessage(QString message);


public slots:
    void sendPing();

signals:
    void readyForUse();
    void newMessage(QString message, int type);
    void userDisconnected();

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

#endif


#endif // TCPCONNECTION_H
