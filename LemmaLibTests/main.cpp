//Copyright (c) 2014, IDEO 

#include "CppUTest/CommandLineTestRunner.h"
#include <QtTest/QtTest>
#include "ConfigFileCheckerTests.h"
#include "EnvironmentVariableReaderTests.h"
#include "EventSenderTests.h"
#include "EventRegistrarTests.h"
#include "MapToSongConverterTests.h"
#include "Noam/EventFilterTests.h"
#include "Noam/EventMessageHandlerTests.h"
#include "Noam/MessageSenderTests.h"
#include "Noam/HostLocatorTests.h"
#include "SocketReaderTests.h"
#include "SongGroupTests.h"
#include "XmlKeyValueParserTests.h"

int main( int ac, char** av )
{
    QCoreApplication app(ac, av);

    ConfigFileCheckerTests configFileChecker;
    Noam::EventMessageHandlerTests eventMessageHandler;
    Noam::EventFilterTests eventFilter;
    EventSenderTests eventSender;
    EventRegistrarTests registrar;
    MessageSenderTests messageSender;
    SocketReaderTests socketReader;
    HostLocatorTests maestroLocater;
    EnvironmentVariableReaderTests environmentVariableReader;
    XmlKeyValueParserTests xmlKeyValueParser;
    SongGroupTests songGroup;
    MapToSongConverterTests mapToSong;

    // One possible solution for this redundnacy:
    //     http://el-tramo.be/git/qttestutil
    if (0 != QTest::qExec(&configFileChecker, ac, av))
        return -1;
    if (0 != QTest::qExec(&eventFilter, ac, av))
        return -1;
    if (0 != QTest::qExec(&eventMessageHandler, ac, av))
        return -1;
    if (0 != QTest::qExec(&eventSender, ac, av) )
        return -1;
    if (0 != QTest::qExec(&registrar, ac, av) )
        return -1;
    if (0 != QTest::qExec(&messageSender, ac, av) )
        return -1;
    if (0 != QTest::qExec(&socketReader, ac, av) )
        return -1;
    if (0 != QTest::qExec(&maestroLocater, ac, av) )
        return -1;
    if (0 != QTest::qExec(&environmentVariableReader, ac, av) )
        return -1;
    if (0 != QTest::qExec(&songGroup, ac, av) )
        return -1;
    if (0 != QTest::qExec(&xmlKeyValueParser, ac, av) )
        return -1;
    if (0 != QTest::qExec(&mapToSong, ac, av) )
        return -1;
    if (0 != CommandLineTestRunner::RunAllTests(ac, av))
        return -1;
    return 0;
}
