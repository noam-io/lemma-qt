//Copyright (c) 2014, IDEO 

#ifndef ENVIRONMENTVARIABLEREADERTESTS_H
#define ENVIRONMENTVARIABLEREADERTESTS_H

#include <QtCore/QObject>

class EnvironmentVariableReader;

class EnvironmentVariableReaderTests : public QObject
{
    Q_OBJECT

private:
    char const * variables[3];
    EnvironmentVariableReader* reader;

private slots:
    void init();
    void cleanup();

    void findsNothing();
    void findsSomething();
};

#endif
