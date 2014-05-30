//Copyright (c) 2014, IDEO 

#ifndef SONG_H
#define SONG_H

class Song
{
private:
    QString title;
    QString artist;
    QString genre;
    QString album;
    QString duration;
    QString location;

public:
    Song();

    const QString& getTitle() const;
    void setTitle( const QString& value );

    const QString& getArtist() const;
    void setArtist( const QString& value );

    const QString& getGenre() const;
    void setGenre( const QString& value );

    const QString& getAlbum() const;
    void setAlbum( const QString& value );

    const QString& getDuration() const;
    void setDuration( const QString& value );

    const QString& getLocation() const;
    void setLocation( const QString& value );
};

#endif
