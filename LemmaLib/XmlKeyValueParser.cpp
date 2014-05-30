//Copyright (c) 2014, IDEO 

#include "XmlKeyValueParser.h"
#include <QtCore/QXmlStreamReader>

static void skipToFirstDictionary( QXmlStreamReader& reader )
{
    while( !reader.atEnd() )
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        if( token == QXmlStreamReader::StartElement )
        {
            if( reader.name() == "dict" )
                return;
        }
    }
}

static QVariantList readArray( QXmlStreamReader& reader );

static QVariantMap readDictionary( QXmlStreamReader& reader )
{
    QVariantMap result;
    while( reader.readNextStartElement() )
    {
        QString key = reader.readElementText();
        reader.readNextStartElement();

        if( "dict" == reader.name() )
        {
            result[ key ] = readDictionary( reader );
        }
        else if( "array" == reader.name() )
        {
            result[ key ] = readArray( reader );
        }
        else
        {
            result[ key ] = reader.readElementText();
        }
    }

    reader.readNext();

    return result;
}

static QVariantList readArray( QXmlStreamReader& reader )
{
    QVariantList result;
    while( reader.readNextStartElement() )
    {
        result.append( readDictionary( reader ));
    }

    return result;
}

QVariantMap XmlKeyValueParser::parse( QByteArray xml )
{
    QXmlStreamReader reader( xml );
    skipToFirstDictionary( reader );
    const QVariantMap& result = readDictionary( reader );
    reader.clear();
    return result;
}
