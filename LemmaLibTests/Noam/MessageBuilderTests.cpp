//Copyright (c) 2014, IDEO 

#include <QtCore/QByteArray>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QVariant>

#include "Noam/MessageBuilder.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(MessageBuilder)
{
    void setup()
    {
    }
    void teardown()
    {
    }
};

TEST(MessageBuilder, BuildRegister)
{
    QString lemmaId( "Lemma Id" );
    QString deviceType( "Device Type" );
    QString systemVersion( "System Version" );

    Noam::MessageBuilder builder( lemmaId );

    QVariantList plays;
    plays.append("event3");
    plays.append("event4");

    QVariantList hears;
    hears.append("event1");
    hears.append("event2");

    QByteArray registerMessage = builder.buildRegister( deviceType, systemVersion, 5534, hears, plays );
    CHECK_EQUAL('[', registerMessage.at(0));
    CHECK(registerMessage.contains("register"));

    QJsonDocument parsedDoc = QJsonDocument::fromJson(registerMessage);
    QJsonArray parsedArray = parsedDoc.array();
    QVariantList parsedList = parsedArray.toVariantList();
    CHECK(parsedList.at(2) == 5534);
    CHECK(parsedList.at(3).toList().at(0) == "event1");
    CHECK(parsedList.at(3).toList().at(1) == "event2");
    CHECK(parsedList.at(4).toList().at(0) == "event3");
    CHECK(parsedList.at(4).toList().at(1) == "event4");
    CHECK( parsedList.at(5) == deviceType );
    CHECK( parsedList.at(6) == systemVersion );
}

TEST(MessageBuilder, BuildEvent)
{
    Noam::MessageBuilder builder("lemmaId");
    QByteArray event = builder.buildEvent( "car_speed", 442.12 );

    CHECK( event.startsWith( '[' ));
    CHECK( event.contains( "car_speed" ));
    CHECK( event.contains( "442.12" ));
    CHECK( event.contains( "event" ));
    CHECK( event.contains( "lemmaId" ));
}
