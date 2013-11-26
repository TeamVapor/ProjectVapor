#include "chatconnection.h"

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout = 60 * 1000;
static const int PingInterval = 5 * 1000;
static const char SeparatorToken = '$';
static const char TerminationToken = 27;
#include <QTimerEvent>
#include <QHostInfo>
#include <QStringList>
ChatConnection::ChatConnection(QObject *parent, QString hostname, QHostInfo info, int portnum) :
    QTcpSocket(parent), mHostName(hostname),mHostInfo(info), mPort(portnum), mConnectState(WaitingForLobbyEntered),
    mCurrentType(Undefined),mCurrentTypeByteCount(-1), mTimerID(0)
{
    mPingTimer.setInterval(PingInterval);
    connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    connect(this, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(&mPingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
    connect(this,SIGNAL(connected()),this,SLOT(sendConnectionEstablished()));
}



QHostAddress ChatConnection::getHostAddress()
{
    return mHostInfo.addresses()[0];
}

QHostInfo ChatConnection::getHostInfo()
{
    return mHostInfo;
}

int ChatConnection::getPort()
{

}

QString ChatConnection::name()
{
    return mHostName;
}

bool ChatConnection::sendMessage(const QString &message)
{
    QByteArray msg = message.toUtf8();
    QByteArray data = "<M> " + QByteArray::number(msg.size()) + ' ' + msg;
    return write(data) == data.size();
}


void ChatConnection::timerEvent(QTimerEvent *timerEvent)
{
    if (timerEvent->timerId() == mTimerID) {
        abort();
        killTimer(mTimerID);
        mTimerID = 0;
    }
}


void ChatConnection::processReadyRead()
{
    if (mConnectState == WaitingForLobbyEntered) {
        if (!readProtocolHeader())
            return;
        if (mCurrentType != HelloLobby) {
            abort();
            return;
        }
        mConnectState = ReadingEnteredLobby;
    }

    if (mConnectState == ReadingEnteredLobby)
    {
        emit newMessage(QString::fromUtf8(mBuffer), mCurrentType);
        mBuffer.clear();

        if (!isValid()) {
            abort();
            return;
        }

        mPingTimer.start();
        mPongTime.start();
        mConnectState = ReadyForUse;
        emit readyForUse();
    }
    else
    {
        // else if not knowing what to expect
        // read till finished then process data
        do {
            if (mCurrentType == Undefined) {
                if (!readProtocolHeader())
                    return;
            }
            if (!hasEnoughData())
                return;
            processData();
        } while (bytesAvailable() > 0);
    }

}

int ChatConnection::readDataIntoBuffer(int maxSize)
{
    if (maxSize > MaxBufferSize)
        return 0;

    int numBytesBeforeRead = mBuffer.size();
    if (numBytesBeforeRead == MaxBufferSize) {
        abort();
        return 0;
    }

    while (bytesAvailable() > 0 && mBuffer.size() < maxSize) {
        mBuffer.append(read(1));
        if (mBuffer.endsWith(SeparatorToken))
            break;
    }
    return mBuffer.size() - numBytesBeforeRead;
}


void ChatConnection::sendPing()
{
    if (mPongTime.elapsed() > PongTimeout) {
        abort();
        return;
    }

    write("<P> hello?");
}


void ChatConnection::sendConnectionEstablished()
{
    QString username = mHostName.split("$$")[0];
    QByteArray entered_lobby = username.toUtf8() + TerminationToken;
    QByteArray message_w_header = "<E> " + QByteArray::number(entered_lobby.size()) + ' ' + entered_lobby;
    write(message_w_header);
}


void ChatConnection::socketDisconnected()
{
    mPingTimer.stop();
    emit userDisconnected();
}

int ChatConnection::dataLengthForCurrentDataType()
{
    if (bytesAvailable() <= 0 || readDataIntoBuffer() <= 0
            || mBuffer.endsWith(SeparatorToken))
        return 0;

    mBuffer.chop(1);
    int number = mBuffer.toInt();
    mBuffer.clear();
    return number;
}


bool ChatConnection::readProtocolHeader()
{
    if (mTimerID) {
        killTimer(mTimerID);
        mTimerID = 0;
    }

    if (readDataIntoBuffer() <= 0) {
        mTimerID = startTimer(TransferTimeout);
        return false;
    }
    if (mBuffer.startsWith("<P> ")) {
        mCurrentType = VaporPing;
    } else if (mBuffer.startsWith("<O> ")) {
        mCurrentType = VaporPong;
    } else if (mBuffer.startsWith("<M> ")) {
        mCurrentType = LobbyMessage;
    } else if (mBuffer.startsWith("<E> ")) {
        mCurrentType = HelloLobby;
        return true;
    } else if (mBuffer.startsWith("<I> ")) {
        mCurrentType = GameInvite;
    } else if (mBuffer.startsWith("<D> ")) {
        mCurrentType = InviteDecline;
    } else if (mBuffer.startsWith("<A> ")) {
        mCurrentType = InviteAccept;
    } else if (mBuffer.startsWith("<G> ")) {
        mCurrentType = GoodByeLobby;
    }
    else {
        mCurrentType = Undefined;
        abort();
        return false;
    }

    mBuffer.clear();
    mCurrentTypeByteCount = dataLengthForCurrentDataType();
    return true;
}



bool ChatConnection::hasEnoughData()
{
    if (mTimerID) {
        QObject::killTimer(mTimerID);
        mTimerID = 0;
    }

    if (mCurrentTypeByteCount <= 0)
        mCurrentTypeByteCount = dataLengthForCurrentDataType();

    if (bytesAvailable() < mCurrentTypeByteCount
            || mCurrentTypeByteCount <= 0) {
        mTimerID = startTimer(TransferTimeout);
        return false;
    }

    return true;
}

void ChatConnection::processData()
{
    mBuffer = read(mCurrentTypeByteCount);
    if (mBuffer.size() != mCurrentTypeByteCount) {
        abort();
        return;
    }

    switch (mCurrentType) {
    case LobbyMessage:
        emit newMessage(QString::fromUtf8(mBuffer), mCurrentType);
        break;
    case VaporPing:
        sendConnectionEstablished();
        break;
    case VaporPong:
    {
        write("<O> I'm Here");
        break;
    }
    case HelloLobby:
        emit newMessage(QString::fromUtf8(mBuffer), mCurrentType);
        break;
    default:
        break;
    }

    mCurrentType = Undefined;
    mCurrentTypeByteCount = 0;
    mBuffer.clear();

}

ChatConnection::~ChatConnection()
{
    mPingTimer.stop();
    disconnect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    disconnect(this, SIGNAL(disconnected()), &mPingTimer, SLOT(stop()));
    disconnect(&mPingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
}
