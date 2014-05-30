//Copyright (c) 2014, IDEO 

#include <QtCore/QByteArray>
#include <QtCore/QString>

#include "Noam/EventMessage.h"
#include "Noam/MessageBuilder.h"
#include "Noam/MessageParseException.h"

#include "CppUTest/TestHarness.h"

TEST_GROUP(EventMessage)
{
    void setup()
    {
    }
    void teardown()
    {
    }
};

TEST(EventMessage, ParseRaw)
{
    Noam::MessageBuilder builder("id12345");
    QByteArray rawMessage = builder.buildEvent("car_speed", 442.12);

    Noam::EventMessage event( rawMessage );
    CHECK( event.type == QString("event") );
    CHECK( event.eventName == QString("car_speed") );
    CHECK( event.eventValue == QVariant(442.12) );
    CHECK( event.lemmaId == "id12345" );
}

TEST(EventMessage, ParseException)
{
    try
    {
        Noam::EventMessage( QByteArray( "Invalid Message" ));
        FAIL( "Expecting a MessageParseException" );
    }
    catch( const Noam::MessageParseException& e )
    {
        STRCMP_EQUAL( "Unable to parse message: Invalid Message", e.what() );
    }
}

TEST( EventMessage, ParseNestedLists )
{
    Noam::MessageBuilder builder( "id12345" );
    QVariantList innerList;
    innerList.append( "a" );
    innerList.append( "b" );
    innerList.append( 3 );

    QVariantList expected;
    expected.append( 5 );
    expected.append( "six" );
    expected.insert( expected.size(), innerList );

    QByteArray rawMessage = builder.buildEvent( "car_speed", expected );

    Noam::EventMessage event( rawMessage );
    CHECK(  expected == event.eventValue.toList() );
}

TEST( EventMessage, ParseMaps )
{
    Noam::MessageBuilder builder( "id12345" );

    QVariantList list1;
    list1.append( 1 );
    list1.append( "two" );

    QVariantList list2;
    list2.append( "three" );
    list2.append( 4 );

    QMap< QString, QVariant > expected;
    expected[ "a" ] = list1;
    expected[ "b" ] = list2;

    QByteArray rawMessage = builder.buildEvent( "car_speed", expected );

    Noam::EventMessage event( rawMessage );
    CHECK(  expected == event.eventValue.toMap() );
}
