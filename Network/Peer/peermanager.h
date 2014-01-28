#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QObject>
#include <QHostInfo>
class PeerManager : public QObject
{
    Q_OBJECT
public:
    explicit PeerManager(QObject *parent = 0);
    QString nickName() const;
    
signals:
    void newUserConnected(QString message);

public slots:
    void lanUsersUpdated();
    void resolveTimedOutUser();
    void userRecordResolved(QHostInfo info, int port);
private:
    QString serviceNameToUsername(QString hostname);

protected:
    QString                   mUserName;

};

#endif // PEERMANAGER_H
