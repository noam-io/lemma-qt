//Copyright (c) 2014, IDEO 

#include "EventMessageHandlerTests.h"

#include <QtTest/QTest>
#include "Noam/EventMessageHandler.h"
#include "Noam/MessageBuilder.h"
#include "Noam/EventMessage.h"

namespace Noam{
    void EventMessageHandlerTests::init()
    {
        listener = new EventMessageHandler();
        connect( listener, &EventMessageHandler::newEvent, this, &EventMessageHandlerTests::event );
    }

    void EventMessageHandlerTests::cleanup()
    {
        delete listener;
    }

    void EventMessageHandlerTests::event( EventMessage & e )
    {
        eventEmitted = e.eventName;
        valueEmitted = e.eventValue;
    }

    void EventMessageHandlerTests::parsesMessages()
    {
        Noam::MessageBuilder builder("id123");
        const QByteArray& message = builder.buildEvent("some event id", 332.89);
        listener->handleMessage( message );

        QCOMPARE( eventEmitted, QVariant("some event id") );
        QCOMPARE( valueEmitted, QVariant(332.89) );
    }

    void EventMessageHandlerTests::parsesListMessages()
    {
        Noam::MessageBuilder builder("id123");
				QVariantList testList;
				testList.append(QVariant(0));
				testList.append(QVariant(6000));
				testList.append(QVariant("Country"));
				QVariantList sublist;
				sublist.append(QVariant("subsub"));
				testList.append(QVariant(sublist));

        const QByteArray& message = builder.buildEvent("some event id", testList);
        listener->handleMessage( message );

        QCOMPARE( eventEmitted, QVariant("some event id") );
				QCOMPARE( (int)valueEmitted.type(), (int)QMetaType::QVariantList);
				QCOMPARE( valueEmitted.canConvert(QMetaType::QVariantList), true);
				QVariantList list = valueEmitted.toList();
        QCOMPARE( valueEmitted.toList()[0],  QVariant(0));
        QCOMPARE( valueEmitted.toList()[1],  QVariant(6000));
        QCOMPARE( valueEmitted.toList()[2],  QVariant("Country"));

				QCOMPARE( (int)valueEmitted.toList()[3].type(), (int)QMetaType::QVariantList);
				QCOMPARE( valueEmitted.toList()[3].canConvert(QMetaType::QVariantList), true);
        QCOMPARE( valueEmitted.toList()[3].toList()[0],  QVariant("subsub"));

    }

    void EventMessageHandlerTests::gracefullyHandlesInvalidMessages()
    {
        listener->handleMessage( "a" );
    }
}
