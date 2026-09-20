#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

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
#include <QMenu>
#include <QVideoWidget>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidgetItem>
#include <QEvent>
#include <QKeyEvent>

namespace Ui {
class VideoWindow;
}

class VideoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoWindow(QWidget *parent = nullptr);
    ~VideoWindow();

private:
    void initPlayer();
    void initNetList();

    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void on_btn_play_clicked();

    void on_online_list_itemDoubleClicked(QListWidgetItem *item);

    void on_btn_pre_clicked();

    void on_btn_next_clicked();

    void on_progress_bar_sliderReleased();

    void durationChanged(int duration);
    void positionChanged(int position);

    void on_btn_full_clicked();

    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    void on_volume_bar_valueChanged(int value);

    void on_btn_back_clicked();

private:
    Ui::VideoWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *output;
    QVideoWidget *videoWid;
    QNetworkAccessManager *manager;

    bool m_isVideoFullScreen = false;



};

#endif // VIDEOWINDOW_H
