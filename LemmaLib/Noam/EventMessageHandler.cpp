//Copyright (c) 2014, IDEO 

#include "EventMessageHandler.h"

#include "Noam/EventMessage.h"
#include "Noam/MessageParseException.h"

namespace Noam{
    EventMessageHandler::EventMessageHandler( QObject *parent ) :
        QObject( parent )
    { }

    void EventMessageHandler::handleMessage( QByteArray rawMessage)
    {
        try
        {
            Noam::EventMessage message( rawMessage );
            emit newEvent( message );
        }
        catch( const Noam::MessageParseException& e )
        {
            qDebug() << e.what();
        }
    }
}
