//Copyright (c) 2014, IDEO 

#include "Noam/TcpProtocol.h"

#include <QtCore/QByteArray>
#include "CppUTest/TestHarness.h"

TEST_GROUP( NoamTcpProtocol )
{ };


TEST( NoamTcpProtocol, EncodesEmptyString )
{
    QByteArray encoded = Noam::TcpProtocol::encode( QByteArray("") );
    QByteArray expected( "000000" );
    STRCMP_EQUAL( expected.data(), encoded.data() );
}

TEST( NoamTcpProtocol, EncodesOneCharacter )
{
    QByteArray encoded = Noam::TcpProtocol::encode( QByteArray("a") );
    QByteArray expected( "000001a" );
    STRCMP_EQUAL( expected.data(), encoded.data() );
}

TEST( NoamTcpProtocol, EncodesManyCharacters )
{
    QByteArray encoded = Noam::TcpProtocol::encode( QByteArray("abcdefghijklmnopqrstuvwxyz") );
    QByteArray expected( "000026abcdefghijklmnopqrstuvwxyz" );
    STRCMP_EQUAL( expected.data(), encoded.data() );
}
