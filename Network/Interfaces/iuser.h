#ifndef IUSER_H
#define IUSER_H

#include <QObject>
#include <QHostAddress>
class iUser : public QObject
{
    Q_OBJECT
class iChatConnection;
public:
    QString getName(){return mUserName;}

    virtual QString getAddress() = 0;
signals:


public slots:
    void setName(QString name){ mUserName = name;}
    virtual void sendMessage(QString message) = 0;
protected:

    QString      mUserName;
    explicit iUser(QObject *parent = 0, QString username = ""):QObject(parent),mUserName(username){}
    iChatConnection * mChatConnection;
};
#endif // IUSER_H
