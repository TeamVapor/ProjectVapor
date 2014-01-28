#ifndef CHATMESSAGEFACTORY_H
#define CHATMESSAGEFACTORY_H
#include "Network/Interfaces/iMessageFactory.h"
class ChatMessageFactory : public QObject, public iMessageFactory
{
    Q_OBJECT
    Q_INTERFACES(iMessageFactory)
public:
    ChatMessageFactory(QObject *parent = 0);
    QString createMessage(int messagetype, QString contents,QString ipaddress, QString name,QString specialheader = "");
    QString createMessageHeader(int messagetype, QString name, QString ipaddress, QString specialheader);
signals:

public slots:

};

#endif // CHATMESSAGEFACTORY_H
