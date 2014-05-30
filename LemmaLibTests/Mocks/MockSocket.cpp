//Copyright (c) 2014, IDEO 

#include "Mocks/MockSocket.h"


MockSocket::MockSocket() :
    Noam::Socket()
  , wasClosed_( false )
  , connectedToPort( 0 )
  , totalConnectionsAttempted( 0 )
{ }

void MockSocket::send( QByteArray data )
{
    ensureIsOpen();
    toSend += data;
    emit readyRead();
}

qint64 MockSocket::bytesAvailable() const
{
    ensureIsOpen();
    return toSend.length();
}

QByteArray MockSocket::read( qint64 maxSize )
{
    ensureIsOpen();

    QByteArray result = toSend.left( maxSize );
    toSend.remove( 0, maxSize );

    return result;
}

qint64 MockSocket::write( const QByteArray & byteArray )
{
    dataSent += byteArray;
    return byteArray.length();
}

void MockSocket::connectToHost( const QHostAddress& address, quint16 port )
{
    totalConnectionsAttempted++;
    connectedToAddress = address;
    connectedToPort = port;
}

void MockSocket::emitConnected()
{
    emit connected();
}

void MockSocket::close()
{
    wasClosed_ = true;
    emit disconnected();
}

void MockSocket::flush()
{ }

bool MockSocket::wasClosed() const
{
    return wasClosed_;
}

void MockSocket::ensureIsOpen() const
{
    if( wasClosed() )
    {
        qDebug() << "Can't operate on a closed socket.";
        throw;
    }
}
