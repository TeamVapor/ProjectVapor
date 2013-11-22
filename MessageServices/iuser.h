#ifndef IUSER_H
#define IUSER_H

#include <QObject>
#include <QHostAddress>
class iUser : public QObject
{
    Q_OBJECT
public:
    QString getName(){return mName;}
    virtual void sendMessage(QString message) = 0;

signals:


public slots:
    void setName(QString name){ mName = name;}

protected:

    QString      mName;
    explicit iUser(QObject *parent = 0):QObject(parent){}

};
#endif // IUSER_H
