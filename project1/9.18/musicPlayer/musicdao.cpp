#include "musicdao.h"

MusicDao::MusicDao() {
    this->db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/code/20/qt/9.18/musicPlayer/sql/music.db");

    if(!db.open()){
        qDebug()<<"数据库打开失败"<<db.lastError().text();
        return;

    }
}

MusicDao::~MusicDao()
{
    this->db.close();
}

void MusicDao::add(Music &music)
{
    QString sql = "insert into music(path_song,path_name,path_lyr) values('%1','%2','%3')" ;
    sql=sql.arg(music.getPath_song()).arg(music.getPath_name()).arg(music.getPath_lyr());

    QSqlQuery query(db);
    if(query.exec(sql)){
        qDebug()<<"新增歌曲成功 新增歌曲:"<<music.getPath_name();
    }else{
        qDebug()<<"新增歌曲失败"<<query.lastError().text();
    }

}

void MusicDao::del(int id)
{
    QString sql = "delete from music where id = %1" ;
    sql=sql.arg(id);

    QSqlQuery query(db);
    if(query.exec(sql)){
        qDebug()<<"删除列表歌曲成功";
    }else{
        qDebug()<<"删除歌曲失败"<<query.lastError().text();
    }
}

QVector<Music> MusicDao::findAll()
{
    QVector<Music> musics;

    QString sql="select * from music";

    QSqlQuery query(db);
    if(query.exec(sql)){
        while (query.next()) {
            int id = query.value("id").toInt();
            QString path = query.value("path_song").toString();
            QString path_name = query.value("path_name").toString();
            QString path_lyr = query.value("path_lyr").toString();
            Music music(id,path,path_name,path_lyr);
            musics.push_back(music);
        }
    }else {
        qDebug()<<"查询失败"<<query.lastError().text();
    }
    return musics;
}
