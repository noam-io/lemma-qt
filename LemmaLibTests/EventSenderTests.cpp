//Copyright (c) 2014, IDEO 

#include "EventSenderTests.h"

#include <QtTest/QTest>
#include "EventSender.h"
#include "Noam/MessageBuilder.h"

void EventSenderTests::emitsMessageToSendSignal()
{
    EventSender eventSender("sp_id");
    connect( &eventSender, &EventSender::messageToSend, this, &EventSenderTests::messageSent );
    eventSender.speak( "name", "value" );

    Noam::MessageBuilder builder("sp_id");
    QByteArray expectedMessage= builder.buildEvent( "name", "value" );
    QCOMPARE( actualMessage.data(), expectedMessage.data() );
}

void EventSenderTests::sendsVariantValues()
{
    EventSender eventSender("1234");
    connect( &eventSender, &EventSender::messageToSend, this, &EventSenderTests::messageSent );

    QVariantList value;
    value.append("value");
    value.append("value2");
    eventSender.speak( "name",  value);

    Noam::MessageBuilder builder("1234");
    QByteArray expectedMessage = builder.buildEvent( "name", value );
    QCOMPARE( actualMessage.data(), expectedMessage.data() );
}

void EventSenderTests::messageSent( QByteArray message )
{
    actualMessage = message;
}
