//Copyright (c) 2014, IDEO 

#ifndef LEMMA_H
#define LEMMA_H

#include <QtCore/QObject>
#include <QtQuick/QQuickView>
#include "Config.h"

namespace Noam{
    class EventFilter;
    class EventMessageHandler;
    class MessageSender;
    class HostLocator;
}

struct LemmaObjects;

class Lemma : public QObject
{
    Q_OBJECT
    Noam::MessageSender* messageSender;
    Noam::HostLocator* locator;
    char** environmentVariables;

public:
    Lemma( QQuickView * view, QString GuestName, QString RoomName = "");
    void start();
    ~Lemma();
    bool *connectedToMaestro;

private:
    void connectWithHostLocator( Noam::MessageSender* sender );    
    void connectWithFilters( Noam::EventMessageHandler* listener, const QList< Noam::EventFilter* >& filters );
    QQuickView * mainView;
    QString lemmaId;
    QString roomName;
    quint16 broadcastPort;
    QString deviceType;
    QString systemVersion;
    LemmaObjects * context;    

public slots:
    void createEventSender();
    void registerFilters( QQuickView::Status status );
    void connectionStatus( QQuickView::Status status );

};

#endif // LEMMA_H
