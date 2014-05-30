//Copyright (c) 2014, IDEO 

#include "EventFilterTests.h"

#include <QtTest/QTest>
#include "Noam/EventFilter.h"
#include "Noam/EventMessage.h"

namespace Noam{
    void EventFilterTests::init()
    {
        filter = new EventFilter();
        connect( filter, &EventFilter::newEvent, this, &EventFilterTests::newEvent );
        connect( filter, &EventFilter::newListEvent, this, &EventFilterTests::newListEvent );
        connect( filter, &EventFilter::newMapEvent, this, &EventFilterTests::newMapEvent );
        eventValue = QVariant();
    }

    void EventFilterTests::cleanup()
    {
        delete filter;
    }

    void EventFilterTests::newEvent( const QVariant& value )
    {
        eventValue = value;
    }

    void EventFilterTests::newListEvent( const QVariantList & value )
    {
        eventListValue = value;
    }

    void EventFilterTests::newMapEvent( const QVariantMap & value )
    {
        eventMapValue = value;
    }

    void EventFilterTests::forwardsRequestedEvents()
    {
        filter->setTopicName( "e1" );
        EventMessage message(QString("e1"), QString("v1"));
        filter->handleEvent( message );
        QCOMPARE( eventValue, QVariant( "v1" ));
    }

    void EventFilterTests::doesNotForwardOtherEvents()
    {
        filter->setTopicName( "e1" );
        EventMessage message("e2", "v2");
        filter->handleEvent( message );
        QCOMPARE( eventValue, QVariant() );
    }

    void EventFilterTests::forwardsMapEvents()
    {
        QVariantMap map;
        map["foo"] = "bar";

        filter->setTopicName( "e1" );
        EventMessage message("e1", map);
        filter->handleEvent( message );
        QCOMPARE( eventMapValue, map );
    }

    void EventFilterTests::forwardsListEvents()
    {
        QVariantList list;
        list.append( "bob" );
        list.append( 5 );

        filter->setTopicName( "e1" );
        EventMessage message("e1", list);
        filter->handleEvent( message );
        QCOMPARE( eventListValue, list );
    }
}
