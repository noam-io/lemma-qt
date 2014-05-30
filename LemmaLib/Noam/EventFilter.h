//Copyright (c) 2014, IDEO 

#ifndef EVENT_FILTER_H
#define EVENT_FILTER_H

#include <QtCore/QObject>

namespace Noam {

    class EventMessage;

    class EventFilter : public QObject
    {
        Q_OBJECT

        Q_PROPERTY( QString topic READ getTopicName WRITE setTopicName )

    private:
        QString triggerName;

    public:
        explicit EventFilter( QObject *parent = 0 );

        QString getTopicName() const;
        void setTopicName( QString name );

    signals:
        void newEvent( QVariant value );
        void newListEvent( QVariantList value );
        void newMapEvent( QVariantMap value );

    public slots:
        void handleEvent( EventMessage & event );
    };
}

#endif
