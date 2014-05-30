//Copyright (c) 2014, IDEO 

#ifndef EVENT_MESSAGE_HANDLER_TESTS_H
#define EVENT_MESSAGE_HANDLER_TESTS_H

#include <QtCore/QObject>
#include <QVariant>

namespace Noam{

    class EventMessageHandler;
    class EventMessage;

    class EventMessageHandlerTests : public QObject
    {
        Q_OBJECT

    private:
        EventMessageHandler* listener;

    public:
        QVariant eventEmitted;
        QVariant valueEmitted;

    public slots:
        void event(EventMessage & e);

    private slots:
        void init();
        void cleanup();

        void parsesMessages();
        void parsesListMessages();
        void gracefullyHandlesInvalidMessages();
    };
}
#endif
