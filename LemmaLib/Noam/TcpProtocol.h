//Copyright (c) 2014, IDEO 

#ifndef Noam_TCPPROTOCOL_H
#define Noam_TCPPROTOCOL_H

class QByteArray;

namespace Noam
{
    class TcpProtocol
    {
    public:
        static QByteArray encode( const QByteArray& dataToSend );

    private:
        TcpProtocol();
    };
}

#endif
