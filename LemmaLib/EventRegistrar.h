//Copyright (c) 2014, IDEO 

#ifndef EVENTREGISTRAR_H
#define EVENTREGISTRAR_H

#include <QtCore/QObject>

namespace Noam { class EventFilter; }

class EventRegistrar : public QObject
{
    Q_OBJECT

    QString lemmaId;
    QString deviceType;
    QString systemVersion;
    quint16 port;
    QList< Noam::EventFilter* > filters;

public:
    explicit EventRegistrar( QString lemmaId, QString deviceType, QString systemVersion, quint16 port, QList< Noam::EventFilter* > filters, QObject *parent = 0 );
    void sendRegistration();

signals:
    void registration( QByteArray message );

};

#endif
