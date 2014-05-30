//Copyright (c) 2014, IDEO 

#ifndef CONNECTIONSTATUSTEST_H
#define CONNECTIONSTATUSTEST_H

#include <QObject>

class ConnectionStatusTest : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionStatusTest(QObject *parent = 0);
    
signals:
    
public slots:
private slots:
    void testCreation();
};

#endif // CONNECTIONSTATUSTEST_H
