//Copyright (c) 2014, IDEO 

#include "EventRegistrarTests.h"

#include <QtTest/QTest>
#include "EventRegistrar.h"
#include "Noam/EventFilter.h"
#include "Noam/MessageBuilder.h"

void EventRegistrarTests::registersFilters()
{
    QString lemmaId( "Lemma Id" );
    QString deviceType( "Device Type" );
    QString systemVersion( "System Version" );

    QList< Noam::EventFilter* > filters;
    Noam::EventFilter filter1;
    filter1.setTopicName("boom");
    filters.append( &filter1 );

    Noam::EventFilter filter2;
    filter2.setTopicName("bam");
    filters.append( &filter2 );

    EventRegistrar registrar( lemmaId, deviceType, systemVersion, 3322, filters );
    connect( &registrar, &EventRegistrar::registration, this, &EventRegistrarTests::registrationReceived );

    registrar.sendRegistration();
    Noam::MessageBuilder builder( lemmaId );
    QVariantList plays;
    QVariantList hears;
    hears.append("boom");
    hears.append("bam");
    QByteArray expectedMessage = builder.buildRegister( deviceType, systemVersion, 3322, hears, plays);

    QCOMPARE( actualMessage.data(), expectedMessage.data() );
}

void EventRegistrarTests::registrationReceived( QByteArray message )
{
    actualMessage = message;
}
