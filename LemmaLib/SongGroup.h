//Copyright (c) 2014, IDEO 

#ifndef SONG_GROUP_H
#define SONG_GROUP_H

#include <QtCore/QString>
#include "Song.h"

class SongGroup
{
private:
    QString name;
    QList< Song > songs;

public:
    SongGroup();
    SongGroup( QString name );
    QString getName() const;
    QList< Song > getSongs() const;
    void addSong( const Song& song );
};

#endif
