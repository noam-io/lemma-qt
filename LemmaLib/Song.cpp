//Copyright (c) 2014, IDEO 

#include "Song.h"

Song::Song()
{ }

const QString& Song::getTitle() const
{
    return title;
}

void Song::setTitle( const QString& value )
{
    title = value;
}

const QString& Song::getGenre() const
{
    return genre;
}

void Song::setGenre( const QString& value )
{
    genre = value;
}

const QString& Song::getArtist() const
{
    return artist;
}

void Song::setArtist( const QString& value )
{
    artist = value;
}

const QString& Song::getAlbum() const
{
    return album;
}

void Song::setAlbum( const QString& value )
{
    album = value;
}

const QString& Song::getDuration() const
{
    return duration;
}

void Song::setDuration( const QString& value )
{
    duration = value;
}

const QString& Song::getLocation() const
{
    return location;
}

void Song::setLocation( const QString& value )
{
    location = value;
}
