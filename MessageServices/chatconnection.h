#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QHostAddress>
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

    ChatConnection(QObject *parent = 0, QString hostname = "");

    QString name() const;
    bool sendMessage(const QString &message);

signals:
    void readyForUse();
    void newMessage(const QString &from, const QString &message);

protected:
    void timerEvent(QTimerEvent *timerEvent);

private slots:
    void processReadyRead();
    void sendPing();
    void sendEnteredLobbyMessage(QString entered_lobby_msg);
    //void sendGameInvite(QString gamename, QString gamesystem, QString target_user);


private:
    int readDataIntoBuffer(int maxSize = MaxBufferSize);
    int dataLengthForCurrentDataType();
    bool readProtocolHeader();
    bool hasEnoughData();
    void processData();
    QString mHostName;
    QTimer mPingTimer;
    QTime mPongTime;
    QByteArray mBuffer;
    ConnectionState mConnectState;
    DataType mCurrentType;
    int mCurrentTypeByteCount;
    int mTimerID;
    bool mEnteredLobbyMessageSent;
};

#endif


#endif // TCPCONNECTION_H
