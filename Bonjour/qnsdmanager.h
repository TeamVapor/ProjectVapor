#ifndef QNSDMANAGER_H
#define QNSDMANAGER_H

#include <QObject>
#include <Bonjour/bonjourservicebrowser.h>
#include <Bonjour/bonjourserviceregister.h>
#include <Bonjour/bonjourserviceresolver.h>
#include <QStringList>
#include <QHostAddress>

class QNSDManager : public QObject
{
    Q_OBJECT

private:
    BonjourServiceBrowser  *mNSDBrowser;
    BonjourServiceRegister *mNSDRegistrar;
    BonjourServiceResolver *mNSDResolver;
    QList<BonjourRecord>    mNSDRecords;
    QString                 mLocalName;


private slots:
    void updateRecords(const QList<BonjourRecord> &list);
    void recordResolved(QHostInfo host_info,int port);

public:
    explicit QNSDManager(QObject *parent = 0);
    void setLocalName(QString name){mLocalName = name;}
    QString getLocalName(){return mLocalName;}
    QStringList getServiceNames();
    void resolveServiceByName(QString exact_name);
    void resolveServciceByType(QString type, QString name);
    void resolveServiceNameContains(QString contained_within);
    void resolveSercviceWithTypeAndNameContains(QString type, QString name_contains);
    bool resloveServiceAtIndex(uint index);

    ~QNSDManager();

signals:
    void recordsChanged();
    void resolvedRecord(QHostInfo host_info,int port);

public slots:
    void registerService(QString service_name, QString service_type, int port);
    void browseService(QString servive_type);
    void unregisterService();
    void forceStopResolving();
};

#endif // QNSDMANAGER_H
