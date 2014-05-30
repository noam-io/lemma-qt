//Copyright (c) 2014, IDEO 

#ifndef Noam_EVENTMESSAGE_H
#define Noam_EVENTMESSAGE_H

#include <QtCore/QString>
#include <QtCore/QVariant>

namespace Noam {
    class EventMessage
    {
    public:
        explicit EventMessage( const QByteArray& raw );
        explicit EventMessage( const QString & name, const QVariant & value );
        QString type;
        QString lemmaId;
        QString eventName;
        QVariant eventValue;
    };
}

#endif
