//Copyright (c) 2014, IDEO 

#ifndef MARCOTIMER_H
#define MARCOTIMER_H

#include <QtCore/QObject>
#include <QTimer>

#include "EventSender.h"
#include "Config.h"

class EventSender;

class MarcoTimer : public QObject
{
    Q_OBJECT

    EventSender* marcoSender;
    QTimer* timer;
    QString roomName;

public:
    explicit MarcoTimer( EventSender* marcoSender , QString roomName = "" );

private slots:
    void signalMarco();

public slots:
    void start();
    void stop();

signals:
    void trySendMarco( QString roomName );

};

#endif // MARCOTIMER_H
