//Copyright (c) 2014, IDEO 

#ifndef POLO_H
#define POLO_H

#include <QtCore/QString>
#include <QtCore/QVariant>

namespace Noam {

    class Polo
    {
    public:
        explicit Polo( const QByteArray& raw );
        QString roomName;
        int port;
    };

}
#endif // POLO_H
