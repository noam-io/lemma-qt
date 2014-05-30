//Copyright (c) 2014, IDEO 

#include "SocketReaderTests.h"

#include <QtTest/QTest>
#include "Mocks/MockSocket.cpp"
#include "SocketReader.h"

void SocketReaderTests::init()
{
    messages = new QList< QByteArray >();

    socket = new MockSocket();
    reader = new SocketReader( socket );
    reader->go();
    connect( reader, &SocketReader::doneReading, this, &SocketReaderTests::messageReceived );
}

void SocketReaderTests::cleanup()
{
    delete messages;
    delete reader;
    delete socket;
}

void SocketReaderTests::messageReceived( QByteArray message )
{
    messages->append( message );
}

void SocketReaderTests::sendMessage( QString message )
{
    socket->send( message.toUtf8() );
}

void SocketReaderTests::readsOneByte()
{
    sendMessage( "000001A" );
    QCOMPARE(messages->first().data(), "A" );
}

void SocketReaderTests::readsTwoBytes()
{
    sendMessage( "000002ZY" );
    QCOMPARE(messages->first().data(), "ZY" );
}

void SocketReaderTests::readsTwoMessages()
{
    sendMessage( "000002KL000003abc" );
    QCOMPARE(messages->first().data(), "KL" );
    QCOMPARE(messages->last().data(), "abc" );
}

void SocketReaderTests::readsThreeMessages()
{
    sendMessage( "000002KL000003abc000001:" );
    QCOMPARE(messages->at(0).data(), "KL" );
    QCOMPARE(messages->at(1).data(), "abc" );
    QCOMPARE(messages->at(2).data(), ":" );
}

void SocketReaderTests::readsInterruptedMessages()
{
    sendMessage( "000" );
    sendMessage( "008" );
    sendMessage( "jo " );
    sendMessage( "momma" );
    QCOMPARE(messages->size(), 1);
    QCOMPARE(messages->first().data(), "jo momma" );
    sendMessage( "000004john" );
    QCOMPARE(messages->size(), 2);
    QCOMPARE(messages->last().data(), "john" );
}

void SocketReaderTests::closesConnectionOnZeroBytes()
{
    sendMessage( "000000" );
    QCOMPARE( messages->size(), 0 );
    QVERIFY( socket->wasClosed() );
}

void SocketReaderTests::closesConnectionOnInvalidMessageLength()
{
    sendMessage( "ffffffa" );
    QCOMPARE( messages->size(), 0 );
    QVERIFY( socket->wasClosed() );
}

