//Copyright (c) 2014, IDEO 

#ifndef XML_KEY_VALUE_PARSER_TESTS_H
#define XML_KEY_VALUE_PARSER_TESTS_H

#include <QtCore/QObject>

class XmlKeyValueParserTests : public QObject
{
    Q_OBJECT
public:
    QByteArray xml;
    
private slots:
    void initTestCase();

    void readsKeysValues();
    void readsArrayValues();
};

#endif
