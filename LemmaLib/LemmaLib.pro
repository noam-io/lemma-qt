#Copyright (c) 2014, IDEO

TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    Config.h \
    SocketReader.h \
    EventSender.h \
    TcpListener.h \
    Noam/MessageParseException.h \
    Noam/TcpProtocol.h \
    EventRegistrar.h \
    Noam/MessageSender.h \
    Noam/MessageBuilder.h \
    Noam/EventMessage.h \
    precompiled.h \
    EnvironmentVariableReader.h \
    Noam/Socket.h \
    Noam/EventMessageHandler.h \
    Noam/EventFilter.h \        
    Noam/ConnectionStatus.h \
    Lemma.h \    
    Config.h \
    Noam/HostLocator.h \
    Noam/Polo.h \
    MarcoTimer.h \
    XmlKeyValueParser.h \
    Song.h \
    SongGroup.h \
    MapToSongConverter.h \
    ConfigFileChecker.h \
    ConfigurationFile.h


SOURCES += \
    SocketReader.cpp \
    EventSender.cpp \
    TcpListener.cpp \
    Noam/MessageParseException.cpp \
    Noam/TcpProtocol.cpp \
    EventRegistrar.cpp \
    Noam/MessageSender.cpp \
    Noam/MessageBuilder.cpp \
    Noam/EventMessage.cpp \
    EnvironmentVariableReader.cpp \
    Noam/Socket.cpp \
    Noam/EventMessageHandler.cpp \
    Noam/EventFilter.cpp \
    Lemma.cpp \
    Noam/HostLocator.cpp \
    Noam/Polo.cpp \
    MarcoTimer.cpp \
    XmlKeyValueParser.cpp \
    Song.cpp \
    SongGroup.cpp \
    MapToSongConverter.cpp \
    ConfigFileChecker.cpp \
    ConfigurationFile.cpp

CONFIG += precompile_header
PRECOMPILED_HEADER = precompiled.h
