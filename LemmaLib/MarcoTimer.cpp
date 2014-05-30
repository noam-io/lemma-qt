//Copyright (c) 2014, IDEO 

#include "MarcoTimer.h"

MarcoTimer::MarcoTimer( EventSender* marcoSender, QString roomName ) :
    marcoSender( marcoSender ),
    timer( new QTimer( this )),
    roomName( roomName )
{
    connect( timer, &QTimer::timeout, this, &MarcoTimer::signalMarco );
}

void MarcoTimer::start(){
    timer->start( MARCO_PERIOD );
}

void MarcoTimer::stop(){
    timer->stop();
}

void MarcoTimer::signalMarco(){
    emit trySendMarco( roomName );
}
