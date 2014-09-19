//Copyright (c) 2014, IDEO 

#include "EventRegistrar.h"

#include "Noam/MessageBuilder.h"
#include "Noam/EventFilter.h"

EventRegistrar::EventRegistrar( QString lemmaId, QString deviceType, QString systemVersion, quint16 port, QList< Noam::EventFilter* > filters, QObject *parent ) :
    QObject( parent )
  , lemmaId( lemmaId )
  , deviceType( deviceType )
  , systemVersion( systemVersion )
  , port( port )
  , filters( filters )
{ }

void EventRegistrar::sendRegistration()
{
    Noam::MessageBuilder builder( lemmaId );
    QVariantList plays;
    QVariantList hears;
    QSet<QString> uniqueHears;

    QList< Noam::EventFilter* >::iterator i = filters.begin();
    while ( i != filters.end() )
    {
        uniqueHears << ( (*i)->getTopicName() );
        ++i;
    }

    QSet<QString>::iterator j = uniqueHears.begin();
    while ( j != uniqueHears.end() )
    {
        hears << ( QVariant(*j) );
        ++j;
    }

    QByteArray message = builder.buildRegister( deviceType, systemVersion, port, hears, plays );
    emit registration( message );
}
