//Copyright (c) 2014, IDEO 

#ifndef XML_KEY_VALUE_PARSER_H
#define XML_KEY_VALUE_PARSER_H

#include <QtCore/QVariant>

class XmlKeyValueParser
{
public:
    QVariantMap parse( QByteArray xml );
};

#endif
