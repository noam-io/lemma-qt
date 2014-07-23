//Copyright (c) 2014, IDEO 

#include "Noam/Socket.h"

namespace Noam {

    Socket::Socket() :
        socket( 0 )
    {}

//    Socket::~Socket(){
//        close();
//    }

    Socket::Socket( QAbstractSocket* socket ) :
        socket( socket )
    {
        connect( socket, &QAbstractSocket::readyRead,
                 this, &Noam::Socket::readyRead );
        connect( socket, &QAbstractSocket::connected,
                 this, &Noam::Socket::connected );
        connect( socket, &QAbstractSocket::disconnected,
                 this, &Noam::Socket::disconnected );
    }

    qint64 Socket::bytesAvailable() const
    {
        return socket->bytesAvailable();
    }

    QByteArray Socket::read( qint64 maxSize )
    {
        return socket->read( maxSize );
    }

    qint64 Socket::write( const QByteArray& byteArray )
    {
        return socket->write( byteArray );
    }

    void Socket::connectToHost( const QHostAddress& address, quint16 port )
    {
        socket->connectToHost( address, port );
    }

    bool Socket::waitForConnected( int msecs = 30000 )
    {
        return socket->waitForConnected( msecs );
    }

    QString Socket::errorString()
    {
        return socket->errorString();
    }

    void Socket::close()
    {
        socket->close();
    }

    void Socket::flush()
    {
        socket->flush();
    }
}
