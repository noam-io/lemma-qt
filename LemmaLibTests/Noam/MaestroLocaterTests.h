//Copyright (c) 2014, IDEO 

#ifndef Noam_MAESTRO_LOCATER_TESTS_H
#define Noam_MAESTRO_LOCATER_TESTS_H

#include <QtCore/QObject>

namespace Noam { class HostLocator; }

class HostLocatorTests : public QObject
{
    Q_OBJECT

    static const quint16 PORT;
    static const QString LOCALHOST;

    QString maestroIp;
    quint16 maestroPort;
    Noam::HostLocator* listener;

private:
    void broadcastMessage( QString message );

public slots:
    void maestroFound( QString ip, quint16 port );

private slots:
    void init();
    void cleanup();

    void listensForMessages();
    void ignoresBadMessages();
};

#endif
