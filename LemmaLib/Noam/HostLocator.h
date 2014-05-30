//Copyright (c) 2014, IDEO 

#ifndef Noam_MAESTRO_LOCATER_H
#define Noam_MAESTRO_LOCATER_H

#include <QtCore/QObject>
#include "../Config.h"
#include "Polo.h"

class QUdpSocket;

namespace Noam
{
    class HostLocator : public QObject
    {
        Q_OBJECT

        quint16 port;
        QUdpSocket* socket;        

    public:
        explicit HostLocator( QObject *parent = 0 );
        void go();

    signals:
        void maestroFound( QString ip, quint16 port );

    public slots:
        void tryMarco( const QByteArray& message );

    private slots:
        void udpDatagramAvailable();        
    };
}

#endif
