//Copyright (c) 2014, IDEO 

#include "Noam/HostLocatorTests.h"

#include <QtTest/QTest>
#include "Noam/HostLocator.h"
#include <QtNetwork/QUdpSocket>
#include <QCoreApplication>

const quint16 HostLocatorTests::PORT = 40837;
const QString HostLocatorTests::LOCALHOST( "127.0.0.1" );

void HostLocatorTests::init()
{
    maestroIp = QString();
    maestroPort = 0;

    listener = new Noam::HostLocator( PORT );
    connect( listener, &Noam::HostLocator::maestroFound, this, &HostLocatorTests::maestroFound );
}

void HostLocatorTests::cleanup()
{
    delete listener;
}

void HostLocatorTests::maestroFound( QString ip, quint16 port )
{
    maestroIp = ip;
    maestroPort = port;
}

void HostLocatorTests::broadcastMessage( QString message )
{
    QUdpSocket udpSocket;
    udpSocket.bind( PORT );
    udpSocket.writeDatagram( message.toLatin1(), QHostAddress::LocalHost, PORT );
    udpSocket.close();
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
}

void HostLocatorTests::listensForMessages()
{
    listener->go();
    broadcastMessage( "[Maestro@45993]" );

    QCOMPARE( maestroIp, LOCALHOST );
    QCOMPARE( maestroPort, (quint16) 45993 );
}

void HostLocatorTests::ignoresBadMessages()
{
    listener->go();
    broadcastMessage( "[Maestro@444" );

    QCOMPARE( maestroIp, QString());
    QCOMPARE( maestroPort, (quint16) 0 );
}
