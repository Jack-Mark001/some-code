#ifndef MUSICDAO_H
#define MUSICDAO_H


#include <QObject>
#include <music.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class MusicDao
{
public:
    MusicDao();
    ~MusicDao();

    void add(Music& music);
    void del(int id);
    QVector<Music> findAll();

    QSqlDatabase db;

};

#endif // MUSICDAO_H
