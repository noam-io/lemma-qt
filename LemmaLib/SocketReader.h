//Copyright (c) 2014, IDEO 

#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QtCore/QObject>

namespace Noam{ class Socket; }

class SocketReader : public QObject
{
    Q_OBJECT

    Noam::Socket* clientSocket;
    qint64 expectedMessageSize;
    QByteArray message;

public:
    explicit SocketReader( Noam::Socket* socket, QObject *parent = 0 );
    void go();

signals:
    void doneReading( QByteArray );

private:
    bool messageSizeDetermined();
    bool messageReadToCompletion();
    bool somethingToRead();
    bool enoughDataToDetermineMessageSize();
    bool determineExpectedMessageSize();
    void readMessage();
    void prepareForNextMessage();

private slots:
    void read();
};

#endif
