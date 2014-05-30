//Copyright (c) 2014, IDEO 

#include "ConfigFileChecker.h"

#include <QtCore/QStringList>

ConfigFileChecker::ConfigFileChecker( QString expected, QString actual ) :
    expected( expected )
  , actual( actual )
{ }

bool ConfigFileChecker::isValid()
{
    return missingFields().count() == 0;
}

static QString parseOutKey( const QString& line )
{
    QString result;
    bool isComment = line.startsWith( '#' );
    if( !isComment )
    {
        const QStringList& keyValue = line.split( "=" );
        if( keyValue.count() > 1 )
        {
            result = keyValue.at( 0 ).trimmed();
        }
    }
    return result;
}

static QSet< QString > extractKeys( const QString& contents )
{
    QSet< QString > result;

    const QStringList& keysValues = contents.split( "\n" );
    for( QStringList::const_iterator begin = keysValues.constBegin(); begin != keysValues.constEnd(); ++begin )
    {
        const QString& key = parseOutKey( *begin );
        if( !key.isEmpty() )
        {
            result.insert( key );
        }
    }
    return result;
}

QSet< QString > ConfigFileChecker::missingFields()
{
    const QSet< QString >& expectedKeys = extractKeys( expected );
    const QSet< QString >& actualKeys = extractKeys( actual );

    return expectedKeys - actualKeys;
}
