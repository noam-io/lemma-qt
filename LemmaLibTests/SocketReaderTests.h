//Copyright (c) 2014, IDEO 

#ifndef SOCKETREADERTESTS_H
#define SOCKETREADERTESTS_H

#include <QtCore/QObject>

class MockSocket;
class SocketReader;

class SocketReaderTests : public QObject
{
    Q_OBJECT

    QList< QByteArray >* messages;
    MockSocket* socket;
    SocketReader* reader;

private:
    void sendMessage( QString message );

private slots:
    void init();
    void cleanup();

    void messageReceived( QByteArray );

    void readsOneByte();
    void readsTwoBytes();
    void readsTwoMessages();
    void readsThreeMessages();
    void readsInterruptedMessages();
    void closesConnectionOnZeroBytes();
    void closesConnectionOnInvalidMessageLength();
};

#endif
