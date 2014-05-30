//Copyright (c) 2014, IDEO 

#ifndef EVENTSENDER_H
#define EVENTSENDER_H

#include <QtCore/QObject>

#include "Config.h"

namespace Noam {
class MessageBuilder;
};

class EventSender : public QObject
{
    Q_OBJECT

public:
    explicit EventSender( QString const & id = "", QObject *parent = 0 );
    virtual ~EventSender();
private:
    Noam::MessageBuilder* builder;

public slots:
    void speak( QString name, QVariant value );
    void sendMarco( QString roomName );

signals:
    void messageToSend( QByteArray message );
    void marcoToSend( QByteArray message );
};

#endif
