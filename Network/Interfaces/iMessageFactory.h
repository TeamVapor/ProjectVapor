#ifndef IMESSAGEFACTORY_H
#define IMESSAGEFACTORY_H

#include <QtCore/QString>
#include <QObject>
class iMessageFactory
{
public:
    virtual QString createMessage(int messagetype, QString contents, QString specialheader = "") =0;
    ~iMessageFactory(){}
};
Q_DECLARE_INTERFACE(
    iMessageFactory,
    "com.Network.Messages.IMessageFactory/1.0"
)

#endif // IMESSAGEFACTORY_H
