#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTime>
#include <QMessageBox>
#include <QRandomGenerator>


#include "music.h"
#include "musicdao.h"
#include "lyrics.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MusicWindow;
}
QT_END_NAMESPACE

class MusicWindow : public QMainWindow
{
    Q_OBJECT

    enum PlayMode{Random,OnceLoop,Loop,Sequence};

public:
    explicit MusicWindow(QWidget *parent = nullptr);
    ~MusicWindow() override;

private slots:
    void on_btn_load_clicked();

    void on_local_list_itemDoubleClicked(QListWidgetItem *item);

    void on_btn_play_clicked();


    void durationChanged(int duration);
    void positionChanged(int position);

    void on_btn_next_clicked();

    void on_btn_pre_clicked();

    void on_progress_bar_sliderReleased();


    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    void loadMusicList();


    void on_btn_mode_clicked();

    void on_btn_mode_triggered(QAction *act);

    // //歌词改变
    void updateLyricDisplay(qint64 position);

    // //切歌加载
    void loadLyricFor(const Music &music);

    void on_volume_bar_valueChanged(int value);

    void on_btn_back_clicked();

private:
    Ui::MusicWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *ouput;
    PlayMode mode=Loop;
    MusicDao dao;
    Lyric lyric;
    int pre_line=-1;
    int m_currentLyricRow = -1;
};
#endif // MUSICWINDOW_H
