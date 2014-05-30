//Copyright (c) 2014, IDEO 

#ifndef MOCKSOCKET_H
#define MOCKSOCKET_H

#include "Noam/Socket.h"
#include <QHostAddress>

class MockSocket : public Noam::Socket
{
    Q_OBJECT

    QByteArray toSend;
    bool wasClosed_;

public:

    QHostAddress connectedToAddress;
    quint16 connectedToPort;
    QByteArray dataSent;
    int totalConnectionsAttempted;

    MockSocket();

    void send( QByteArray data );
    bool wasClosed() const;
    void emitConnected();


    virtual qint64 bytesAvailable() const;
    virtual QByteArray read( qint64 maxSize );
    virtual qint64 write( const QByteArray & byteArray );

    virtual void close();
    virtual void flush();

    virtual void connectToHost( const QHostAddress& address, quint16 port );

private:
    void ensureIsOpen() const;

};

#endif
