//Copyright (c) 2014, IDEO 

#include "MessageParseException.h"

#include <QtCore/QByteArray>
#include <QtCore/QString>

Noam::MessageParseException::MessageParseException( const QByteArray& message )
    : std::runtime_error( generateErrorMessage( message ).toStdString() )
{ }

QString Noam::MessageParseException::generateErrorMessage( const QByteArray& message )
{
    return QString("Unable to parse message: ")
            .append( message.data() );
}
