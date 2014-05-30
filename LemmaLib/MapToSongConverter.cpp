//Copyright (c) 2014, IDEO 

#include "MapToSongConverter.h"
#include "Song.h"
#include "SongGroup.h"

QList< SongGroup > MapToSongConverter::groupBySong( const QVariantMap& map )
{
    QList< SongGroup > result;

    const QVariantMap& tracks = map[ "Tracks" ].toMap();

    QVariantMap::const_iterator begin = tracks.constBegin();
    QVariantMap::const_iterator end = tracks.constEnd();
    while( begin != end )
    {
        const QVariantMap& songMap = begin.value().toMap();
        const Song& song = buildSong( songMap );

        SongGroup songGroup( song.getTitle() );
        songGroup.addSong( song );

        result.append( songGroup );

        ++begin;
    }

    return result;
}

QList< SongGroup > MapToSongConverter::groupByAllSongs( const QVariantMap& map )
{
    QList< SongGroup > result;
    SongGroup songGroup( "All Songs" );
    const QVariantMap& tracks = map[ "Tracks" ].toMap();

    QVariantMap::const_iterator begin = tracks.constBegin();
    QVariantMap::const_iterator end = tracks.constEnd();
    while( begin != end )
    {
        const QVariantMap& songMap = begin.value().toMap();
        const Song& song = buildSong( songMap );

        songGroup.addSong( song );

        ++begin;
    }

    result.append( songGroup );
    return result;
}

Song MapToSongConverter::buildSong( const QVariantMap& songMap )
{
    Song song;
    song.setTitle( songMap[ "Name" ].toString() );
    song.setArtist( songMap[ "Artist" ].toString() );
    song.setGenre( songMap[ "Genre" ].toString() );
    song.setAlbum( songMap[ "Album" ].toString() );
    song.setDuration( songMap[ "Total Time" ].toString() );
    song.setLocation( songMap[ "Location" ].toString() );
    return song;
}

QList< SongGroup > MapToSongConverter::groupBy( const QString& field, const QVariantMap& map )
{
    if( field == "Playlist" )
    {
        return groupByPlaylist( map );
    }
    else if( field == "Song" )
    {
        return groupBySong( map );
    }
    else if( field == "AllSongs" )
    {
        return groupByAllSongs( map );
    }
    else
    {
        return groupByField( field, map );
    }
}

void MapToSongConverter::addPlaylistItemsTo( SongGroup& songGroup, const QVariantList& playlistItems, const QVariantMap& tracks )
{
    QVariantList::const_iterator begin = playlistItems.constBegin();
    QVariantList::const_iterator end = playlistItems.constEnd();
    while( begin != end )
    {
        const QString& songId = ( *begin ).toMap()[ "Track ID" ].toString();
        const Song& song = buildSong( tracks[ songId ].toMap() );
        songGroup.addSong( song );

        ++begin;
    }
}

QList< SongGroup > MapToSongConverter::groupByPlaylist( const QVariantMap& map )
{
    QMap< QString, SongGroup > result;

    const QVariantList& playLists = map[ "Playlists" ].toList();
    const QVariantMap& tracks = map[ "Tracks" ].toMap();

    QVariantList::const_iterator begin = playLists.constBegin();
    QVariantList::const_iterator end = playLists.constEnd();
    while( begin != end )
    {
        const QVariantMap& playlist = ( *begin ).toMap();
        const QString& playlistName = playlist[ "Name" ].toString();
        const QVariantList& playlistItems = playlist[ "Playlist Items" ].toList();

        SongGroup songGroup( playlistName );
        addPlaylistItemsTo( songGroup, playlistItems, tracks );
        if( songGroup.getSongs().count() >0 )
        {
            result.insert( playlistName, songGroup );
        }

        ++begin;
    }

    return result.values();
}

QList< SongGroup > MapToSongConverter::groupByField( const QString& field, const QVariantMap& map )
{
    QMap< QString, SongGroup > result;

    const QVariantMap& tracks = map[ "Tracks" ].toMap();

    QVariantMap::const_iterator begin = tracks.constBegin();
    QVariantMap::const_iterator end = tracks.constEnd();
    while( begin != end )
    {
        const QVariantMap& songMap = begin.value().toMap();
        if( songMap.contains( field ))
        {
            const Song& song = buildSong( songMap );

            const QString& fieldValue = songMap[ field ].toString();

            if( !result.contains( fieldValue ))
            {
                result.insert( fieldValue, SongGroup( fieldValue ));
            }
            result[ fieldValue ].addSong( song );
        }
        ++begin;
    }

    return result.values();
}
