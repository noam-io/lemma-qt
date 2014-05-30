//Copyright (c) 2014, IDEO 

#ifndef MAP_TO_SONG_CONVERTER_TESTS_H
#define MAP_TO_SONG_CONVERTER_TESTS_H

#include <QtCore/QObject>
#include "MapToSongConverter.h"
#include <QVariantMap>

class MapToSongConverterTests : public QObject
{
    Q_OBJECT

private:
    QString playlist1Name, playlist2Name;
    QString song1Id, song2Id, song3Id;
    QVariantMap song1, song2, song3;

    MapToSongConverter converter;

private:
    void assertSongs( const Song& song1, const Song& song2, const Song& song3 );
    QVariantMap buildMapOfTracks();
    QVariantList buildListOfPlaylists();

private slots:
    void init();

    void groupsByCategory();
    void groupsSongsWithSameCategory();
    void ignoresEmptyCategories();

    void parsesPlayLists();
    void ignoresEmptyPlayLists();

    void groupsByAllSongs();
    void groupsBySongs();
};

#endif
