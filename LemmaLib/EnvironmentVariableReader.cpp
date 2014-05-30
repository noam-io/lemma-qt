//Copyright (c) 2014, IDEO 

#include "EnvironmentVariableReader.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

EnvironmentVariableReader::EnvironmentVariableReader( char const * const * variables ) :
    variables( variables )
{ }


QString EnvironmentVariableReader::read( QString name ) const
{
    for( int i = 0; variables[i] != 0; ++i )
    {
        QString variable( variables[i] );
        QStringList nameValuePair = variable.split( "=" );
        if( nameValuePair.size() == 2 && nameValuePair.at(0) == name )
            return nameValuePair.at(1);
    }
    QString result;
    return result;
}
