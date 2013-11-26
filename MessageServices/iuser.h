#ifndef IUSER_H
#define IUSER_H

#include <QObject>
#include <QHostAddress>
class iUser : public QObject
{
    Q_OBJECT
public:
    QString getName(){return mUserName;}
    virtual void sendMessage(QString message) = 0;

signals:


public slots:
    void setName(QString name){ mUserName = name;}

protected:

    QString      mUserName;
    explicit iUser(QObject *parent = 0, QString username = ""):QObject(parent),mUserName(username){}

};
#endif // IUSER_H
