//Copyright (c) 2014, IDEO 

#include "EventFilter.h"

#include "EventMessageHandler.h"
#include "Noam/EventMessage.h"

namespace Noam{
    EventFilter::EventFilter(QObject *parent) :
        QObject(parent)
    { }

    void EventFilter::setTopicName( QString name )
    {
        this->triggerName = name;
    }

    QString EventFilter::getTopicName() const
    {
        return triggerName;
    }

    void EventFilter::handleEvent( EventMessage & e)
    {
        if( e.eventName == triggerName )
        {
            if( e.eventValue.canConvert( QVariant::List ))
            {
                emit newListEvent( e.eventValue.toList() );
            }
            else if( e.eventValue.canConvert( QVariant::Map ))
            {
                emit newMapEvent( e.eventValue.toMap() );
            }
            else
            {
                emit newEvent( e.eventValue );
            }
        }
    }
}
