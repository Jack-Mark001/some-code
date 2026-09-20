#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>

class Music
{
public:
    Music();
    Music(int id, const QString &path_song, const QString &path_name, const QString &path_lyr);


    int getId() const;
    void setId(int newId);
    QString getPath_song() const;
    void setPath_song(const QString &newPath_song);
    QString getPath_name() const;
    void setPath_name(const QString &newPath_name);
    QString getPath_lyr() const;
    void setPath_lyr(const QString &newPath_lyr);

private:
    int id;
    QString path_song;
    QString path_name;
    QString path_lyr;

};

#endif // MUSIC_H
