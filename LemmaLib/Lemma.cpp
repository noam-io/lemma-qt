//Copyright (c) 2014, IDEO 

#include "Lemma.h"

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlContext>
#include <QtNetwork/QTcpSocket>

#include "EventSender.h"
#include "EventRegistrar.h"
#include "Noam/EventFilter.h"
#include "Noam/ConnectionStatus.h"
#include "Noam/EventMessageHandler.h"
#include "Noam/Socket.h"
#include "Noam/MessageSender.h"
#include "Noam/HostLocator.h"
#include "TcpListener.h"
#include "MarcoTimer.h"

struct LemmaObjects {
    QTcpSocket * senderSocket;
    Noam::Socket* socket;
    Noam::MessageSender* messageSender;
    EventSender* eventSender;
    Noam::EventMessageHandler* eventListener;
    TcpListener* tcpListener;
    EventRegistrar * registrar;
    Noam::HostLocator* locator;
    MarcoTimer* marcoSendTimer;
};

Lemma::Lemma( QQuickView * view, QString guestName,
              QString roomName )
  : mainView( view )
  , lemmaId( guestName )
  , roomName( roomName )
  , broadcastPort( BROADCAST_SEND_PORT )
  , deviceType( DEVICE_TYPE )
  , systemVersion( PROTOCOL_VERSION )
  , context( new LemmaObjects() )  
{}

void Lemma::start()
{
    qmlRegisterType<Noam::EventFilter>("Lemma", 1, 0, "NoamLemmaHears");
    qmlRegisterType<Noam::ConnectionStatus>("Lemma", 1, 0, "NoamConnectionStatus");
    connect( mainView, &QQuickView::statusChanged, this, &Lemma::registerFilters );
    connect( mainView, &QQuickView::statusChanged, this, &Lemma::connectionStatus);    
    createEventSender();
}

Lemma::~Lemma()
{
    if (context->socket)    //need to close and delete socket first to hang up correctly with server
        context->socket->close();
        delete context->socket;
    if (context->locator)
        delete context->locator;
    if (context->registrar)
        delete context->registrar;
    if (context->tcpListener)
        delete context->tcpListener;
    if (context->eventListener)
        delete context->eventListener;
    if (context->eventSender)
        delete context->eventSender;
    if (context->messageSender)
        delete context->messageSender;
    if (context->senderSocket)
        delete context->senderSocket;
    if (context->marcoSendTimer)
        delete context->marcoSendTimer;
    
    delete context;
}

void Lemma::createEventSender()
{
    QQuickItem* root = mainView->rootObject();
    context->senderSocket = new QTcpSocket( this );
    context-> socket = new Noam::Socket( context->senderSocket );    
    context->messageSender =  new Noam::MessageSender( context->socket, mainView );

    context->eventSender =  new EventSender( lemmaId, root );

    connectWithHostLocator( context->messageSender );    

    connect( context->eventSender, &EventSender::marcoToSend, context->locator, &Noam::HostLocator::tryMarco );
    connect( context->eventSender, &EventSender::messageToSend, context->messageSender, &Noam::MessageSender::send);    

    mainView->rootContext()->setContextProperty( "noamLemma", context->eventSender );
}

void Lemma::connectionStatus(QQuickView::Status status)
{
    if (status == QQuickView::Ready)
    {
        QQuickItem* root = mainView->rootObject();
        QList< Noam::ConnectionStatus* > connectioners = root->findChildren< Noam::ConnectionStatus* >();
        QList< Noam::ConnectionStatus* >::const_iterator begin = connectioners.begin();
        QList< Noam::ConnectionStatus* >::const_iterator end = connectioners.end();
        while( begin != end )
        {
            connect( context->messageSender, &Noam::MessageSender::connectedToMaestro, (*begin), &Noam::ConnectionStatus::connectionEstablished );
            connect( context->messageSender, &Noam::MessageSender::connectionLost, (*begin), &Noam::ConnectionStatus::connectionLost );
            ++begin;
        }
    }
}

void Lemma::registerFilters( QQuickView::Status status )
{
    if (status == QQuickView::Ready)
    {
        QQuickItem* root = mainView->rootObject();

        context->eventListener = new Noam::EventMessageHandler( mainView );
        context->tcpListener = new TcpListener( mainView );
        context->tcpListener->connect(context->tcpListener, &TcpListener::newMessage, context->eventListener, &Noam::EventMessageHandler::handleMessage);
        context->tcpListener->start();

        QList< Noam::EventFilter* > filters = root->findChildren< Noam::EventFilter* >();
        connectWithFilters( context->eventListener, filters );
    
        if (systemVersion.isEmpty())
            systemVersion = mainView->rootObject()->property("version").toString();

        context->registrar =
            new EventRegistrar( lemmaId, deviceType, systemVersion, context->tcpListener->getPort(), filters, mainView );
        connect( context->registrar, &EventRegistrar::registration, context->messageSender, &Noam::MessageSender::send);
        connect( context->messageSender, &Noam::MessageSender::connectedToMaestro, context->registrar, &EventRegistrar::sendRegistration);
    }
}

void Lemma::connectWithFilters( Noam::EventMessageHandler* listener, const QList< Noam::EventFilter* >& filters )
{
    QList< Noam::EventFilter* >::const_iterator begin = filters.begin();
    QList< Noam::EventFilter* >::const_iterator end = filters.end();
    while( begin != end )
    {
        connect( listener, &Noam::EventMessageHandler::newEvent, (*begin), &Noam::EventFilter::handleEvent );
        ++begin;
    }
}

void Lemma::connectWithHostLocator( Noam::MessageSender* sender )
{
    context->locator = new Noam::HostLocator( this );
    connect( context->locator, &Noam::HostLocator::maestroFound, sender, &Noam::MessageSender::connectToMaestro );

    context->marcoSendTimer = new MarcoTimer( context->eventSender , roomName );
    connect( context->marcoSendTimer, &MarcoTimer::trySendMarco, context->eventSender, &EventSender::sendMarco );
    connect( context->messageSender, &Noam::MessageSender::connectedToMaestro, context->marcoSendTimer, &MarcoTimer::stop );
    connect( context->messageSender, &Noam::MessageSender::connectionLost, context->marcoSendTimer, &MarcoTimer::start );
    context->marcoSendTimer->start();
    context->locator->go();
}
