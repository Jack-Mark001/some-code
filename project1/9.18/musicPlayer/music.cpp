#include "music.h"

#include <QObject>


Music::Music() {}

int Music::getId() const
{
    return id;
}

void Music::setId(int newId)
{
    id = newId;
}

QString Music::getPath_song() const
{
    return path_song;
}

void Music::setPath_song(const QString &newPath_song)
{
    path_song = newPath_song;
}

QString Music::getPath_name() const
{
    return path_name;
}

void Music::setPath_name(const QString &newPath_name)
{
    path_name = newPath_name;
}

QString Music::getPath_lyr() const
{
    return path_lyr;
}

void Music::setPath_lyr(const QString &newPath_lyr)
{
    path_lyr = newPath_lyr;
}

Music::Music(int id, const QString &path_song, const QString &path_name, const QString &path_lyr) : id(id),
    path_song(path_song),
    path_name(path_name),
    path_lyr(path_lyr)
{}
