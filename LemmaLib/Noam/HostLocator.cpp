//Copyright (c) 2014, IDEO 

#include "Noam/HostLocator.h"
#include <QtNetwork/QUdpSocket>

Noam::HostLocator::HostLocator( QObject *parent) :
    QObject( parent )
  , port( BROADCAST_SEND_PORT )
  , socket( new QUdpSocket( this ))
{
    connect( socket, &QUdpSocket::readyRead, this, &HostLocator::udpDatagramAvailable );
//    connect( timer, &QTimer::timeout, this, &HostLocator::tryMarco );
}

void Noam::HostLocator::udpDatagramAvailable()
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());

    QHostAddress address;
    socket->readDatagram( datagram.data(), datagram.size(), &address );

    Noam::Polo* polo = new Noam::Polo( datagram.data() );
    if( polo ){
        qDebug() << "Received Polo: " << datagram.data();

        quint16 port = polo->port;

        emit maestroFound( address.toString(), port );
    }
}

void Noam::HostLocator::tryMarco( const QByteArray& message )
{
    qDebug() << "Sending Marco: " << message;
    socket->writeDatagram( message , QHostAddress("255.255.255.255") , port );
}

void Noam::HostLocator::go()
{
    socket->bind( 0, QUdpSocket::ShareAddress );
    qDebug() << "Starting Locator.";
}
