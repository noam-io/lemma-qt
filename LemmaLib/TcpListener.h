//Copyright (c) 2014, IDEO 

#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include <QtCore/QObject>

class QTcpServer;
class SocketReader;

class TcpListener : public QObject
{
    Q_OBJECT

    QTcpServer* server;

public:
    explicit TcpListener( QObject *parent = 0 );
    virtual ~TcpListener() throw();
    void start();
    quint16 getPort();

private slots:
    void registerClient();
    void messageReceived( QByteArray );

signals:
    void newMessage( QByteArray );
};

#endif
