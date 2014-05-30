//Copyright (c) 2014, IDEO 

#ifndef Noam_SOCKET_H
#define Noam_SOCKET_H

#include <QtCore/QObject>

class QAbstractSocket;
class QHostAddress;

namespace Noam {

    class Socket : public QObject
    {
        Q_OBJECT

        QAbstractSocket* socket;

    public:
        Socket();
        Socket( QAbstractSocket* socket );
//        ~Socket();

        virtual qint64 bytesAvailable() const;
        virtual QByteArray read( qint64 maxSize );
        virtual qint64 write( const QByteArray & byteArray );

        virtual void connectToHost( const QHostAddress& address, quint16 port );

        virtual void close();
        virtual void flush();

    signals:
        void readyRead();
        void connected();
        void disconnected();
    };

}

#endif
