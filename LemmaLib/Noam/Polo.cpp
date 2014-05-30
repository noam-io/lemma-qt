//Copyright (c) 2014, IDEO 

#include "Polo.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include "MessageParseException.h"
namespace Noam {
    Polo::Polo( const QByteArray& raw )
    {
        QJsonDocument parsedDoc = QJsonDocument::fromJson(raw);
        QJsonArray parsedArray = parsedDoc.array();
        QVariantList parsedList = parsedArray.toVariantList();
        if( 3 != parsedList.size() )
        {
            throw MessageParseException( raw );
        }

        roomName = parsedList.at(1).toString();
        port = parsedList.at(2).toInt();
    }
}
