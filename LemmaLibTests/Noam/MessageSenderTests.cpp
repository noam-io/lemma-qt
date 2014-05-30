//Copyright (c) 2014, IDEO 

#include "MessageSenderTests.h"

#include <QtTest/QTest>
#include "Noam/MessageSender.h"
#include "Mocks/MockSocket.h"
#include "Noam/TcpProtocol.h"

const quint16 MessageSenderTests::PORT = 44005;
const QString MessageSenderTests::ADDRESS( "127.0.0.1" );

void MessageSenderTests::init()
{
    connectedToMaestroSignalEmitted = false;
    connectionLostSignalEmitted = false;

    socket = new MockSocket();
    sender = new Noam::MessageSender( socket );

    connect( sender, &Noam::MessageSender::connectedToMaestro,
             this, &MessageSenderTests::connectedToMaestro );

    sender->connectToMaestro( ADDRESS, PORT );
}

void MessageSenderTests::cleanup()
{
    delete sender;
    delete socket;
}

void MessageSenderTests::connectsToTheGivenAddressAndPort()
{
    socket->emitConnected();
    QCOMPARE( ADDRESS, socket->connectedToAddress.toString() );
    QCOMPARE( PORT, socket->connectedToPort );
}

void MessageSenderTests::emitsSignalOnConnection()
{
    socket->emitConnected();
    QVERIFY( connectedToMaestroSignalEmitted );
}

void MessageSenderTests::sendsOneMessage()
{
    socket->emitConnected();
    sender->send( "four" );
    QByteArray expectedMessage =  Noam::TcpProtocol::encode( "four" );

    QCOMPARE( socket->dataSent, expectedMessage );
}

void MessageSenderTests::sendsTwoMessages()
{
    socket->emitConnected();
    sender->send( "message 1" );
    sender->send( "message 2" );
    QByteArray message1 = Noam::TcpProtocol::encode( "message 1" );
    QByteArray message2 = Noam::TcpProtocol::encode( "message 2" );
    QByteArray expectedMessage = message1 + message2;

    QCOMPARE( socket->dataSent, expectedMessage );
}

void MessageSenderTests::queuesMessagesUntilConnected()
{
    sender->send( "message 1" );
    sender->send( "message 2" );
    sender->send( "message 3" );
    socket->emitConnected();
    sender->send( "message 4" );

    QByteArray m1 = Noam::TcpProtocol::encode( "message 1" );
    QByteArray m2 = Noam::TcpProtocol::encode( "message 2" );
    QByteArray m3 = Noam::TcpProtocol::encode( "message 3" );
    QByteArray m4 = Noam::TcpProtocol::encode( "message 4" );
    QByteArray expectedMessage = m1 + m2 + m3 + m4;

    QCOMPARE( socket->dataSent, expectedMessage );
}

void MessageSenderTests::sendsMessagesIfImmediatelyConnected()
{
    socket->emitConnected();
    sender->send( "message 1" );
    sender->send( "message 2" );

    QByteArray m1 = Noam::TcpProtocol::encode( "message 1" );
    QByteArray m2 = Noam::TcpProtocol::encode( "message 2" );
    QByteArray expectedMessage = m1 + m2;

    QCOMPARE( socket->dataSent, expectedMessage );
}

void MessageSenderTests::doesNotReconnectWhenCalledTwice()
{
    socket->emitConnected();
    sender->connectToMaestro( ADDRESS, PORT );
    QCOMPARE( 1, socket->totalConnectionsAttempted );
}

void MessageSenderTests::emitDisconnection()
{
    connect( sender, &Noam::MessageSender::connectionLost,
             this, &MessageSenderTests::connectionLost );
    socket->emitConnected();
    socket->close();

    QCOMPARE(true, connectionLostSignalEmitted );
}

void MessageSenderTests::reconnectsWhenDisconnected()
{
    socket->emitConnected();
    socket->close();
    sender->connectToMaestro( ADDRESS, PORT );

    QCOMPARE( 2, socket->totalConnectionsAttempted );
}

void MessageSenderTests::connectedToMaestro()
{
    connectedToMaestroSignalEmitted = true;
}


void MessageSenderTests::connectionLost()
{
    connectionLostSignalEmitted = true;
}
