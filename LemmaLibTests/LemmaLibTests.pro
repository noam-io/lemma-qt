#Copyright (c) 2014, IDEO

QT += core network testlib

SOURCES += \
    main.cpp \
    EventSenderTests.cpp \
    EventRegistrarTests.cpp \
    Noam/MessageSenderTests.cpp \
    Noam/MessageBuilderTests.cpp \
    Noam/EventMessageTests.cpp \
    Noam/HostLocatorTests.cpp \
    EnvironmentVariableReaderTests.cpp \
    SocketReaderTests.cpp \
    Mocks/MockSocket.cpp \
    Noam/EventMessageHandlerTests.cpp \
    Noam/EventFilterTests.cpp \
    ConfigFileCheckerTests.cpp \
    Noam/ConnectionStatusTest.cpp \
    Noam/TcpProtocolTests.cpp

INCLUDEPATH += \
    . \
    $$PWD/../LemmaLib \
    $$PWD/../CppUTest/include

DEPENDPATH +=.

LIBS += -L../LemmaLib -lLemmaLib

target.path = /home/pi/SpallaTests
INSTALLS += target

CONFIG(target) {
    LIBS += -L$$PWD/../CppUTest/arm/lib/ -lCppUTest
} else {
    LIBS += -L$$PWD/../CppUTest/lib/ -lCppUTest
}

HEADERS += \
    EventSenderTests.h \
    EventRegistrarTests.h \
    Noam/MessageSenderTests.h \
    precompiled.h \
    Noam/HostLocatorTests.h \
    EnvironmentVariableReaderTests.h \
    SocketReaderTests.h \
    Mocks/MockSocket.h \
    Noam/EventMessageHandlerTests.h \
    Noam/EventFilterTests.h \
    XmlKeyValueParserTests.h \
    MapToSongConverterTests.h \
    SongGroupTests.h \
    ConfigFileCheckerTests.h \
    Noam/ConnectionStatusTest.h

#CONFIG += precompile_header
#PRECOMPILED_HEADER = precompiled.h

OTHER_FILES +=

 iTunesLibrary.source = iTunes-Library.xml
 DEPLOYMENTFOLDERS += iTunesLibrary

installPrefix = /home/pi/$${TARGET}
iTunesLibraryFile.path = $${installPrefix}
iTunesLibraryFile.files = iTunes-Library.xml
INSTALLS += iTunesLibraryFile



include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()
