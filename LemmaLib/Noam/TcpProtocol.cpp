//Copyright (c) 2014, IDEO 

#include "TcpProtocol.h"

#include <QtCore/QByteArray>
#include <QtCore/QTextStream>

QByteArray Noam::TcpProtocol::encode( const QByteArray& dataToSend )
{
    QByteArray result;
    QTextStream textStream( &result );
    textStream << qSetFieldWidth( 6 ) << qSetPadChar( '0' ) << right << dataToSend.length();
    textStream << qSetFieldWidth( 0 ) << dataToSend;
    textStream.flush();

    return result;
}
