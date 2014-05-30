//Copyright (c) 2014, IDEO 

#include "ConnectionStatusTest.h"
#include "Noam/ConnectionStatus.h"

ConnectionStatusTest::ConnectionStatusTest(QObject *parent) :
    QObject(parent)
{
}


void ConnectionStatusTest::testCreation()
{
    Noam::ConnectionStatus status;
}
