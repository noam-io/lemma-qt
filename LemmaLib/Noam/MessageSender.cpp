//Copyright (c) 2014, IDEO 

#include "MessageSender.h"

#include <QtNetwork/QHostAddress>
#include "Noam/Socket.h"
#include "Noam/TcpProtocol.h"

namespace Noam
{
    MessageSender::MessageSender( Socket* outSocket, QObject* parent) :
        QObject(parent)
      , outSocket( outSocket )
      , isConnected( false )
      , connectionAttempted( false )
    {
        connect( outSocket, &Socket::connected, this, &MessageSender::connected );
        connect( outSocket, &Socket::disconnected, this, &MessageSender::disconnected );
    }

    void MessageSender::connectToMaestro( QString address, quint16 port )
    {
        if( !connectionAttempted )
        {
            connectionAttempted = true;
            qDebug() << "Attempting connection to Host@" << address << ":" << port;
            outSocket->connectToHost( QHostAddress(address), port );
        }
    }

    void MessageSender::send( QByteArray message )
    {
        if( isConnected )
        {
            sendThroughSocket( message );
        }
        else
        {
            queuedMessages.append( message );
        }
    }

    void MessageSender::connected()
    {
        qDebug() << "Connected to Noam Host.";
        isConnected = true;
        emit connectedToMaestro();
        while( !queuedMessages.empty() )
        {
            sendThroughSocket( queuedMessages.takeFirst() );
        }
    }

    void MessageSender::disconnected()
    {
        qDebug() << "Disconnected from Noam Host.";
        isConnected = false;
        connectionAttempted = false;
        emit connectionLost();
    }

    void MessageSender::sendThroughSocket( const QByteArray& message )
    {
        const QByteArray& dataToSend = Noam::TcpProtocol::encode( message );
        outSocket->write( dataToSend );
        outSocket->flush();
    }
}
