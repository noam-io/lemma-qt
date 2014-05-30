//Copyright (c) 2014, IDEO 

#ifndef EVENTSENDERTESTS_H
#define EVENTSENDERTESTS_H

#include <QtCore/QObject>

class EventSenderTests : public QObject
{
    Q_OBJECT

private:
    QByteArray actualMessage;

private slots:
   void emitsMessageToSendSignal();
   void sendsVariantValues();

public slots:
   void messageSent( QByteArray message );
};

#endif
