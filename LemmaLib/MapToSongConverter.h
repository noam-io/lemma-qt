//Copyright (c) 2014, IDEO 

#ifndef MAPTOSONGCONVERTER_H
#define MAPTOSONGCONVERTER_H

#include <QtCore/QObject>

class Song;
class SongGroup;

class MapToSongConverter
{
public:
    QList< SongGroup > groupBy( const QString& field, const QVariantMap& map );

private:
    static Song buildSong( const QVariantMap& songMap );
    static void addPlaylistItemsTo( SongGroup& songGroup, const QVariantList& playlistItems, const QVariantMap& tracks );

    QList< SongGroup > groupBySong( const QVariantMap& map );
    QList< SongGroup > groupByAllSongs( const QVariantMap& map );
    QList< SongGroup > groupByPlaylist( const QVariantMap& map );
    QList< SongGroup > groupByField( const QString& field, const QVariantMap& map );

};

#endif
