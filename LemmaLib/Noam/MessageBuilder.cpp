//Copyright (c) 2014, IDEO 

#include "MessageBuilder.h"

Noam::MessageBuilder::MessageBuilder( QString lemmaId ) :
    lemmaId(lemmaId)
{ }

QByteArray Noam::MessageBuilder::buildEvent(QString name, QVariant value) const
{
  QVariantList list;
  list.append("event");
  list.append(lemmaId);
  list.append(name);
  list.append(value); return serialize(list);
}

QByteArray Noam::MessageBuilder::serialize(QVariantList & list) const
{
  QJsonArray array = QJsonArray::fromVariantList(list);
  QJsonDocument doc(array);
  return doc.toJson().simplified();
}

QByteArray Noam::MessageBuilder::buildRegister( QString deviceType, QString systemVersion, quint16 port, QVariantList & hears, QVariantList & plays ) const
{
  QVariantList list;
  list.append( "register" );
  list.append( lemmaId );
  list.append( port );
  list.append( QVariant( hears ));
  list.append( QVariant( plays ));
  list.append( deviceType );
  list.append( systemVersion );
  return serialize( list );
}

QByteArray Noam::MessageBuilder::buildMarco( QString roomName ) const
{
  QVariantList list;
  list.append( "marco" );
  list.append( lemmaId );
  list.append( roomName );
  list.append( DEVICE_TYPE );
  list.append( PROTOCOL_VERSION );
  return serialize( list );
}
