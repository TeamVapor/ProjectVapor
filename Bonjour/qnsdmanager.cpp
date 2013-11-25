#include "qnsdmanager.h"
#include <QVariant>
#include <QHostInfo>
#include "Bonjour/bonjourrecord.h"
QNSDManager::QNSDManager(QObject *parent) :
    QObject(parent),mNSDResolver(new BonjourServiceResolver(this)), mNSDBrowser(0), mNSDRegistrar(new BonjourServiceRegister(this)),
    mLocalName(QHostInfo::localHostName())
{
    connect(mNSDResolver,SIGNAL(bonjourRecordResolved(QHostInfo,int)),this,SLOT(recordResolved(QHostInfo,int)));

}



void QNSDManager::browseService(QString servive_type)
{

    if(mNSDBrowser != 0)
    {
        disconnect(mNSDBrowser, SIGNAL(currentBonjourRecordsChanged(const QList<BonjourRecord> &)),
                this, SLOT(updateRecords(const QList<BonjourRecord> &)));
        delete mNSDBrowser;
    }
    mNSDBrowser = new BonjourServiceBrowser(this);
    connect(mNSDBrowser, SIGNAL(currentBonjourRecordsChanged(const QList<BonjourRecord> &)),
            this, SLOT(updateRecords(const QList<BonjourRecord> &)));
    mNSDBrowser->browseForServiceType(servive_type);
}





QStringList QNSDManager::getServiceNames()
{
    QStringList ret_list;
    foreach(BonjourRecord record, mNSDRecords)
    {
        ret_list.append(record.serviceName);
    }
    return ret_list;
}


void QNSDManager::recordResolved(QHostInfo host_info, int port)
{
    //qDebug() << host_info.hostName() << " found at "<< host_info.addresses().first().toString();
    emit resolvedRecord(host_info,port);
}

void QNSDManager::registerService(QString service_name, QString service_type, int port)
{
    if(mNSDRegistrar == 0)
        mNSDRegistrar = new BonjourServiceRegister(this);
    mNSDRegistrar->registerService(BonjourRecord(QString("%1 on %2").arg(mLocalName,service_name),
                                                                 service_type, QString()),port);
}

bool QNSDManager::resloveServiceAtIndex(uint index)
{
    // gaurd statement on records list
    if(index >= mNSDRecords.length())
        return false;
    // grab and resolve record, return true
    const BonjourRecord & record(mNSDRecords.at(index));
    mNSDResolver->resolveBonjourRecord(record);
    return true;
}

void QNSDManager::resolveServiceByName(QString exact_name)
{
    foreach(BonjourRecord record, mNSDRecords)
    {
        if(record.serviceName == exact_name)
        {
            if(mNSDResolver == 0)
                mNSDResolver = new BonjourServiceResolver(this);
            mNSDResolver->resolveBonjourRecord(record);
            continue;
        }

    }
}

void QNSDManager::resolveServciceByType(QString type, QString name)
{
    foreach(BonjourRecord record, mNSDRecords)
    {
        if(record.serviceName == name && record.registeredType == type)
        {
            if(mNSDResolver == 0)
                mNSDResolver = new BonjourServiceResolver(this);
            mNSDResolver->resolveBonjourRecord(record);
            continue;
        }

    }
}

void QNSDManager::resolveServiceNameContains(QString contained_within)
{
    foreach(BonjourRecord record, mNSDRecords)
    {
        if(record.serviceName.contains(contained_within))
        {
            if(mNSDResolver == 0)
                mNSDResolver = new BonjourServiceResolver(this);
            mNSDResolver->resolveBonjourRecord(record);
            continue;
        }

    }
}


void QNSDManager::resolveSercviceWithTypeAndNameContains(QString type, QString name_contains)
{
    foreach(BonjourRecord record, mNSDRecords)
    {
        if(record.serviceName.contains(name_contains) && record.registeredType == type)
        {
            if(mNSDResolver == 0)
                mNSDResolver = new BonjourServiceResolver(this);
            mNSDResolver->resolveBonjourRecord(record);
            continue;
        }
    }
}

void QNSDManager::unregisterService()
{
    delete mNSDRegistrar;
    mNSDRegistrar = 0;
}


void QNSDManager::updateRecords(const QList<BonjourRecord> &list)
{

    mNSDRecords.clear();
    QVariant variant;
    foreach (BonjourRecord record, list) {
        variant.setValue(record);
        //qDebug() << record.serviceName + " " +record.registeredType;
        mNSDRecords.append(record);
    }
    emit recordsChanged();
}


QNSDManager::~QNSDManager()
{
    delete mNSDBrowser;
    delete mNSDResolver;
    delete mNSDRegistrar;
    mNSDRecords.clear();
}
