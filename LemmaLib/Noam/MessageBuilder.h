//Copyright (c) 2014, IDEO 

#ifndef Noam_MESSAGEBUILDER_H
#define Noam_MESSAGEBUILDER_H

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "../Config.h"

namespace Noam {
    class MessageBuilder
    {
    private:
        QString lemmaId;
        QByteArray serialize( QVariantList & list ) const;

    public:
        MessageBuilder( QString lemmaId = "" );
        QByteArray buildEvent( QString name, QVariant Value ) const;
        QByteArray buildRegister( QString deviceType, QString systemVersion, quint16 port, QVariantList & hears, QVariantList & plays ) const;
        QByteArray buildMarco( QString roomName ) const;
    };
}

#endif
