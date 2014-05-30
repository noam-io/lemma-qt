//Copyright (c) 2014, IDEO 

#ifndef EVENT_MESSAGE_HANDLER_H
#define EVENT_MESSAGE_HANDLER_H

#include <QtCore/QObject>

namespace Noam{
    class EventMessage;
    class EventMessageHandler : public QObject
    {
        Q_OBJECT

    public:
        explicit EventMessageHandler( QObject *parent = 0 );

    signals:
       // void newEvent(QVariant name, QVariant value);
        void newEvent(EventMessage & e);

    public slots:
        void handleMessage( QByteArray );
    };
}

#endif
