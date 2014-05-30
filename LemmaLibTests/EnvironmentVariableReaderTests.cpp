//Copyright (c) 2014, IDEO 

#include "EnvironmentVariableReaderTests.h"

#include <QtTest/QTest>
#include "EnvironmentVariableReader.h"

void EnvironmentVariableReaderTests::init()
{
    variables[0] = "bob=bob a roo";
    variables[1] = "apple=cinnamon";
    variables[2] = 0;

    reader = new EnvironmentVariableReader( variables );
}

void EnvironmentVariableReaderTests::cleanup()
{
    delete reader;
}

void EnvironmentVariableReaderTests::findsNothing()
{
    QString expected;
    QCOMPARE( reader->read( "boom" ), expected );
}

void EnvironmentVariableReaderTests::findsSomething()
{
    QCOMPARE( reader->read( "bob" ), QString("bob a roo") );
}
