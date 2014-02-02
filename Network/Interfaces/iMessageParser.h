#ifndef IMESSAGEPARSER_H
#define IMESSAGEPARSER_H

#include <QtCore/QString>
#include <QObject>
class iMessageParser : public QObject
{
    Q_OBJECT

public:
  virtual QString parseMessage(QString message, QString& content,int& messagetype) = 0;

protected:
    explicit iMessageParser(QObject *parent = 0) :QObject(parent){}
};

#endif // IMESSAGEPARSER_H
