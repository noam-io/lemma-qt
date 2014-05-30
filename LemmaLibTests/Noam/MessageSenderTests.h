//Copyright (c) 2014, IDEO 

#ifndef MESSAGESENDERTESTS_H
#define MESSAGESENDERTESTS_H

#include <QtCore/QObject>

class MockSocket;

namespace Noam { class MessageSender; }

class MessageSenderTests : public QObject
{
    Q_OBJECT

    static const quint16 PORT;
    static const QString ADDRESS;

    bool connectedToMaestroSignalEmitted;
    bool connectionLostSignalEmitted;
    
    Noam::MessageSender* sender;
    MockSocket* socket;

public slots:
    void connectedToMaestro();
    void connectionLost();

private slots:
    void init();
    void cleanup();

    void connectsToTheGivenAddressAndPort();
    void emitsSignalOnConnection();
    void sendsOneMessage();
    void sendsTwoMessages();
    void queuesMessagesUntilConnected();
    void sendsMessagesIfImmediatelyConnected();
    void doesNotReconnectWhenCalledTwice();
    void reconnectsWhenDisconnected();
    void emitDisconnection();
};

#endif
