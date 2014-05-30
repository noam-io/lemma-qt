//Copyright (c) 2014, IDEO 

#include "EventMessage.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include "MessageParseException.h"

Noam::EventMessage::EventMessage( const QString & name, const QVariant & value ) :
    eventName(name),
    eventValue(value)
{
}

Noam::EventMessage::EventMessage( const QByteArray& raw )
{
    QJsonDocument parsedDoc = QJsonDocument::fromJson(raw);
    QJsonArray parsedArray = parsedDoc.array();
    QVariantList parsedList = parsedArray.toVariantList();

    if( 4 != parsedList.size() )
    {
        throw MessageParseException( raw );
    }

    type = parsedList.at(0).toString();
    lemmaId = parsedList.at(1).toString();
    eventName = parsedList.at(2).toString();
    eventValue = parsedList.at(3);
}
