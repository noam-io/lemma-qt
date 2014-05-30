//Copyright (c) 2014, IDEO 

#include "SocketReader.h"

#include "Noam/Socket.h"

SocketReader::SocketReader( Noam::Socket* clientSocket, QObject *parent ) :
    QObject( parent )
  , clientSocket( clientSocket )
{
    prepareForNextMessage();
}

void SocketReader::go()
{
    connect( clientSocket, &Noam::Socket::disconnected, clientSocket, &SocketReader::deleteLater );
    connect( clientSocket, &Noam::Socket::readyRead, this, &SocketReader::read );
}

void SocketReader::prepareForNextMessage()
{
    expectedMessageSize = -1;
    message = QByteArray();
}

bool SocketReader::messageSizeDetermined()
{
    return expectedMessageSize != -1;
}

bool SocketReader::messageReadToCompletion()
{
    return message.size() == expectedMessageSize;
}

bool SocketReader::somethingToRead()
{
    return clientSocket->bytesAvailable() > 0;
}

bool SocketReader::enoughDataToDetermineMessageSize()
{
    return clientSocket->bytesAvailable() >= 6;
}

void SocketReader::read()
{
    while( somethingToRead() )
    {
        if( messageSizeDetermined() )
        {
            readMessage();
        }
        else if ( enoughDataToDetermineMessageSize() )
        {
            if( !determineExpectedMessageSize() )
            {
                clientSocket->close();
                return;
            }
        }
        else
        {
            return;
        }
    }
}

bool SocketReader::determineExpectedMessageSize()
{
    const QByteArray& socketData = clientSocket->read(6);
    QString messageSize( socketData );

    bool conversionSuccess;
    expectedMessageSize = messageSize.toUtf8().toInt( &conversionSuccess );

    bool result = conversionSuccess && expectedMessageSize > 0;
    return result;
}

void SocketReader::readMessage()
{
    qint64 bytesLeftToRead = expectedMessageSize - message.size();

    message +=  clientSocket->read( bytesLeftToRead );

    if( messageReadToCompletion() )
    {
        emit doneReading( message );
        prepareForNextMessage();
    }
}
