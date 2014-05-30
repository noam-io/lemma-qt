//Copyright (c) 2014, IDEO 

#include "SongGroup.h"

SongGroup::SongGroup()
{ }

SongGroup::SongGroup(QString name) :
    name( name )
{ }

QString SongGroup::getName() const
{
    return name;
}

QList< Song > SongGroup::getSongs() const
{
    return songs;
}

void SongGroup::addSong( const Song& song )
{
    songs.append( song );
}
