//Copyright (c) 2014, IDEO 

#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include <QtCore/QObject>

namespace Noam {
    class ConnectionStatus : public QObject
    {
        Q_OBJECT

    public:
        explicit ConnectionStatus( QObject *parent = 0 ) : QObject(parent) {}

    signals:
        void connectionEstablished();
        void connectionLost();
    };
}
#endif // CONNECTIONSTATUS_H
