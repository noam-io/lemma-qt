//Copyright (c) 2014, IDEO 

#include "EventSender.h"
#include "Noam/MessageBuilder.h"

EventSender::EventSender( QString const & id, QObject *parent ) :
    QObject( parent ) ,  builder(new Noam::MessageBuilder(id))
{ }

EventSender::~EventSender()
{
	delete builder;
}

void EventSender::speak( QString name, QVariant value )
{
    const QByteArray& message = builder->buildEvent( name, value );
    emit messageToSend( message );
}

void EventSender::sendMarco( QString roomName )
{
    const QByteArray& message = builder->buildMarco( roomName );
    emit marcoToSend( message );    
}
