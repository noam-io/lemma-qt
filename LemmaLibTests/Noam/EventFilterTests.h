//Copyright (c) 2014, IDEO 

#ifndef EVENT_FILTER_TESTS_H
#define EVENT_FILTER_TESTS_H

#include <QtCore/QObject>
#include <QVariant>

namespace Noam{

    class EventFilter;

    class EventFilterTests : public QObject
    {
        Q_OBJECT

    private:
        QVariant eventValue;
        QVariantList eventListValue;
        QVariantMap eventMapValue;
        EventFilter* filter;

    private slots:
        void init();
        void cleanup();

        void forwardsRequestedEvents();
        void doesNotForwardOtherEvents();
        void forwardsMapEvents();
        void forwardsListEvents();

        void newEvent( const QVariant& value );
        void newListEvent( const QVariantList & value );
        void newMapEvent( const QVariantMap & value );
    };
}
#endif
