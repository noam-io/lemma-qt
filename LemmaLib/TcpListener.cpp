//Copyright (c) 2014, IDEO 

#include "TcpListener.h"

#include <QtNetwork/QTcpServer>
#include "SocketReader.h"
#include "Noam/Socket.h"

TcpListener::TcpListener( QObject *parent ) :
    QObject( parent )
  , server( new QTcpServer(this) )
{
    connect( server, &QTcpServer::newConnection, this, &TcpListener::registerClient );
}

TcpListener::~TcpListener() throw()
{
    server->close();
}

quint16 TcpListener::getPort()
{
    return server->serverPort();
}

void TcpListener::start()
{
    if( server->listen() ) {
        qDebug() << "Listening succesfully on port" << getPort();
    } else {
        qDebug() << "Failed to listen.";
    }
}

void TcpListener::registerClient()
{
    qDebug() << "Received connection...";
    QTcpSocket* clientConnection = server->nextPendingConnection();
    Noam::Socket* socket = new Noam::Socket( clientConnection );
    SocketReader* reader = new SocketReader( socket, this );
    connect( reader, &SocketReader::doneReading, this, &TcpListener::messageReceived );
    reader->go();
}

void TcpListener::messageReceived( QByteArray message )
{
    emit newMessage( message );
}
