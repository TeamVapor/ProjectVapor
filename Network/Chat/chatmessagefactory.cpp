#include "chatmessagefactory.h"
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
ChatMessageFactory::ChatMessageFactory(QObject *parent) :
    QObject(parent)
{
}


QString ChatMessageFactory::createMessage(int messagetype, QString contents,QString ipaddress, QString name,QString specialheader)
{
    return "";
}

QString ChatMessageFactory::createMessageHeader(int messagetype, QString name, QString ipaddress, QString specialheader)
{

}
