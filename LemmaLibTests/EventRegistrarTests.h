//Copyright (c) 2014, IDEO 

#ifndef EVENTREGISTRARTESTS_H
#define EVENTREGISTRARTESTS_H

#include <QtCore/QObject>

class EventRegistrarTests : public QObject
{
    Q_OBJECT

    QByteArray actualMessage;

public slots:
    void registrationReceived( QByteArray message );

private slots:
    void registersFilters();

};

#endif
