//Copyright (c) 2014, IDEO 

#ifndef Noam_MESSAGESENDER_H
#define Noam_MESSAGESENDER_H

#include <QtCore/QObject>

namespace Noam
{
    class Socket;

    class MessageSender : public QObject
    {
        Q_OBJECT

        Socket* outSocket;
        QList< QByteArray > queuedMessages;
        public: bool isConnected;
        bool connectionAttempted;

    public:
        explicit MessageSender( Socket* outSocket, QObject* parent = 0 );

    signals:
        void connectedToMaestro();
        void connectionLost();

    private:
        void sendThroughSocket( const QByteArray& message );
        void sendQueuedEvents();

    private slots:
        void connected();
        void disconnected();

    public slots:
        void connectToMaestro( QString ip, quint16 port );
        void send( QByteArray message );
    };
}

#endif
