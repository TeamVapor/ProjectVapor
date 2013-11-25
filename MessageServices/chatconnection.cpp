#include "chatconnection.h"

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout = 60 * 1000;
static const int PingInterval = 5 * 1000;
static const char SeparatorToken = '$';
#include <QTimerEvent>
#include <QHostInfo>
ChatConnection::ChatConnection(QObject *parent,QString hostname) :
    QTcpSocket(parent)
{
    mHostName = tr("unknown");
    mConnectState = WaitingForLobbyEntered;
    mCurrentType = Undefined;
    mCurrentTypeByteCount = -1;
    mTimerID = 0;
    mEnteredLobbyMessageSent = false;
    mPingTimer.setInterval(PingInterval);

    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::connect(this, SIGNAL(disconnected()), &mPingTimer, SLOT(stop()));
    QObject::connect(&mPingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
    QObject::connect(this, SIGNAL(connected()),
                     this, SLOT(sendEnteredLobbyMessage()));
}


QString ChatConnection::name() const
{
    return mHostName;
}

bool ChatConnection::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return false;

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

    if (mConnectState == ReadingEnteredLobby) {
        if (!hasEnoughData())
            return;

        mBuffer = read(mCurrentTypeByteCount);
        if (mBuffer.size() != mCurrentTypeByteCount) {
            abort();
            return;
        }

        mHostName = QString(mBuffer) + '@' + peerAddress().toString() + ':'
                   + QString::number(peerPort());
        mCurrentType = Undefined;
        mCurrentTypeByteCount = 0;
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

void ChatConnection::sendPing()
{
    if (mPongTime.elapsed() > PongTimeout) {
        abort();
        return;
    }

    write("<P> hello?");
}


void ChatConnection::sendEnteredLobbyMessage(QString entered_lobby_msg)
{
    QByteArray entered_lobby = entered_lobby_msg.toUtf8();
    QByteArray message_w_header = "<E> " + QByteArray::number(entered_lobby.size()) + ' ' + entered_lobby;
    if (write(message_w_header) == message_w_header.size())
        mEnteredLobbyMessageSent = true;
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


int ChatConnection::dataLengthForCurrentDataType()
{
    if (bytesAvailable() <= 0 || readDataIntoBuffer() <= 0
            || !mBuffer.endsWith(SeparatorToken))
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

    if (mBuffer == "<P> ") {
        mCurrentType = VaporPing;
    } else if (mBuffer == "<O> ") {
        mCurrentType = VaporPong;
    } else if (mBuffer == "<M> ") {
        mCurrentType = LobbyMessage;
    } else if (mBuffer == "<E> ") {
        mCurrentType = HelloLobby;
    } else if (mBuffer == "<I> ") {
        mCurrentType = GameInvite;
    } else if (mBuffer == "<D> ") {
        mCurrentType = InviteDecline;
    } else if (mBuffer == "<A> ") {
        mCurrentType = InviteAccept;
    } else if (mBuffer == "<G> ") {
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
        emit newMessage(mHostName, QString::fromUtf8(mBuffer));
        break;
    case VaporPing:
        write("<O> I'm Here");
        break;
    case VaporPong:
        mPongTime.restart();
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
    QObject::disconnect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::disconnect(this, SIGNAL(disconnected()), &mPingTimer, SLOT(stop()));
    QObject::disconnect(&mPingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
    QObject::disconnect(this, SIGNAL(connected()),
                     this, SLOT(sendEnteredLobbyMessage()));
}
