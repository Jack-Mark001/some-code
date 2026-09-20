#include "musicwindow.h"
#include "ui_musicwindow.h"
#include <QMenu>

MusicWindow::MusicWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MusicWindow)
{
    ui->setupUi(this);

    ui->btn_play->setProperty("mode","play");

    this->player=new QMediaPlayer;
    this->ouput=new QAudioOutput;

    player->setAudioOutput(this->ouput);

    this->ouput->setVolume(1.0);

    connect(this->player,&QMediaPlayer::durationChanged,this,&MusicWindow::durationChanged);
    connect(this->player,&QMediaPlayer::positionChanged,this,&MusicWindow::positionChanged);

    ui->volume_bar->setValue(100);
    this->ouput->setVolume(ui->volume_bar->value()/100);
    ui->volume->setText("100");

    connect(this->player, &QMediaPlayer::mediaStatusChanged,this, &MusicWindow::onMediaStatusChanged);

    // connect(player, &QMediaPlayer::positionChanged,this, &MusicWindow::onPositionChanged);
    //展示数据库里面的歌
    this->loadMusicList();

    //设置toolbutton
    QMenu *menu=new QMenu;

    menu->addAction("循环播放");
    menu->addAction("随机播放");
    menu->addAction("单曲循环");
    menu->addAction("顺序播放");

    ui->btn_mode->setMenu(menu);
    ui->label_now->setText("00:00:00");


    //启动时判断数据库是否有歌，有歌把第一首歌设置默认item
    if(ui->local_list->count()>0){
        ui->local_list->setCurrentItem(ui->local_list->item(0));
        QListWidgetItem *item = ui->local_list->currentItem();
        if (!item) return;

        QString path = item->data(Qt::UserRole).toString();
        this->player->setSource(QUrl::fromLocalFile(path));

        //加载歌词
        int id = item->data(Qt::UserRole + 1).toInt();
        for (const Music &m : dao.findAll()) {
            if (m.getId() == id) { loadLyricFor(m); break; }
        }
    }

}

MusicWindow::~MusicWindow()
{
    delete ui;
}

void MusicWindow::on_btn_load_clicked()
{
    QStringList paths=QFileDialog::getOpenFileNames(this,"选择一首或多首MP3文件","D:/code/resource/music","*.mp3");

    //设置默认值，判断
    //遍历路径，然后用item来接收
    for(QString path:paths){
        QListWidgetItem *item=new QListWidgetItem;
        QFileInfo info(path);
        QString name=info.fileName();
        item->setText(name);
        item->setData(Qt::UserRole,path);
        ui->local_list->addItem(item);


        //把歌曲添加到数据库
        Music music;
        music.setPath_song(path);
        music.setPath_name(name);
        //寻找歌词
        QString lrcPath=info.absolutePath()+"/"+info.baseName()+"-歌词.lrc";
        if(!QFile::exists(lrcPath)){
            lrcPath.clear();
        }
        music.setPath_lyr(lrcPath);
        dao.add(music);
    }

    if(ui->local_list->count()>0){
        ui->local_list->setCurrentItem(ui->local_list->item(0));
        this->player->setSource(QUrl::fromLocalFile(paths.at(0)));
    }

}


void MusicWindow::on_local_list_itemDoubleClicked(QListWidgetItem *item)
{
    //拿到路径
    QString path=item->data(Qt::UserRole).toString();

    this->player->setSource(QUrl::fromLocalFile(path));

    int id = item->data(Qt::UserRole + 1).toInt();
    for (const Music &m : dao.findAll()) {
        if (m.getId() == id) {
            loadLyricFor(m);
            break;
        }
    }

    this->player->play();
    ui->btn_play->setProperty("mode","pause");

    ui->btn_play->style()->unpolish(ui->btn_play);
    ui->btn_play->style()->polish(ui->btn_play);
    ui->btn_play->update();

}


void MusicWindow::on_btn_play_clicked()
{
    if(ui->local_list->count()==0){
        QMessageBox::warning(this,"警告","列表中没有歌曲，请添加歌曲后播放");
        return;
    }
    QString mode=ui->btn_play->property("mode").toString();
    if(mode=="pause"){
        ui->btn_play->setProperty("mode","play");
        this->player->pause();
    }else{
        ui->btn_play->setProperty("mode","pause");
        this->player->play();
    }

    //刷新
    ui->btn_play->style()->unpolish(ui->btn_play);
    ui->btn_play->style()->polish(ui->btn_play);
    ui->btn_play->update();


}



void MusicWindow::durationChanged(int duration)
{
    ui->progress_bar->setMaximum(duration);

    QTime time(0,0,0);
    time=time.addMSecs(duration);

    QString t=time.toString("HH:mm:ss");

    ui->label_all->setText(t);
}

void MusicWindow::positionChanged(int position)
{
    if(!ui->progress_bar->isSliderDown()){
        ui->progress_bar->setValue(position);
    }


    QTime time(0,0,0);
    time=time.addMSecs(position);

    QString t=time.toString("HH:mm:ss");

    ui->label_now->setText(t);

    updateLyricDisplay(position);
}


void MusicWindow::on_btn_next_clicked()
{
    int index=0;
    if(mode==Random){
        index = QRandomGenerator::global()->bounded(ui->local_list->count());
    }else{
        if(mode==Loop || mode==Sequence){
            index=ui->local_list->currentRow();
            if(index==ui->local_list->count()-1){
                index=0;
            }else{
                index++;
            }
        }else if(mode==OnceLoop){
            index=ui->local_list->currentRow();
        }

    }
    ui->local_list->setCurrentRow(index);
    this->on_local_list_itemDoubleClicked(ui->local_list->currentItem());
}


void MusicWindow::on_btn_pre_clicked()
{
    int index=0;
    if(mode==Random){
        index = QRandomGenerator::global()->bounded(ui->local_list->count());
    }else{
        if(mode==Loop || mode==Sequence){
        index=ui->local_list->currentRow();
        if(index==0){
            index=ui->local_list->count()-1;
        }else{
            index--;
        }
        }else if(mode==OnceLoop){
            index=ui->local_list->currentRow();
        }
    }
    ui->local_list->setCurrentRow(index);
    this->on_local_list_itemDoubleClicked(ui->local_list->currentItem());
}


void MusicWindow::on_progress_bar_sliderReleased()
{
    int value=ui->progress_bar->value();

    this->player->setPosition(value);

    this->player->play();

    // qDebug()<<value;
    ui->btn_play->setProperty("mode","pause");

    ui->btn_play->style()->unpolish(ui->btn_play);
    ui->btn_play->style()->polish(ui->btn_play);
    ui->btn_play->update();

}




void MusicWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        this->on_btn_next_clicked();
    }
}


void MusicWindow::loadMusicList()
{
    ui->local_list->clear();                 // 先清空，避免重复

    QVector<Music> musics = dao.findAll(); // 查数据库

    for (const Music &m : musics) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(m.getPath_name());     // 显示歌名/文件名
        item->setData(Qt::UserRole, m.getPath_song());   // 存音频路径
        item->setData(Qt::UserRole + 1, m.getId());      // 存 id，方便删除
        ui->local_list->addItem(item);
    }

    // 默认选中第一个
    if (ui->local_list->count() > 0){
        ui->local_list->setCurrentRow(0);
    }
}



void MusicWindow::on_btn_mode_clicked()
{
    ui->btn_mode->showMenu();
}


void MusicWindow::on_btn_mode_triggered(QAction *act)
{
    QString text=act->text();
    qDebug()<<text;

    if(text=="循环播放"){
        this->mode=Loop;
    }else if(text=="随机播放"){
        this->mode=Random;
    }else if(text=="单曲循环"){
        this->mode=OnceLoop;
    }else if(text=="顺序播放"){
        this->mode=Sequence;
    }

    ui->btn_mode->setText(text);

}

void MusicWindow::updateLyricDisplay(qint64 position)
{
    if (lyric.isEmpty()) return;

    int row = lyric.indexAt(position);
    if (row < 0 || row == m_currentLyricRow) return;   // 行没变不刷新

    m_currentLyricRow = row;

    ui->label_prel->setText(lyric.prevText(row));   // 上方
    ui->label_nowl->setText(lyric.textAt(row));      // 当前
    ui->label_next->setText(lyric.nextText(row));   // 下方
}

void MusicWindow::loadLyricFor(const Music &music)
{
    lyric = Lyric();
    pre_line = -1;

    ui->label_prel->clear();
    ui->label_nowl->clear();
    ui->label_next->clear();

    QString lrcPath = music.getPath_lyr();
    if (lrcPath.isEmpty() || !QFile::exists(lrcPath)) {
        ui->label_nowl->setText("暂无歌词");
        return;
    }

    if (!lyric.load(lrcPath)) {
        ui->label_nowl->setText("歌词解析失败");
        return;
    }
}


void MusicWindow::on_volume_bar_valueChanged(int value)
{
    float v=value/100.0f;

    this->ouput->setVolume(v);

    ui->volume->setText(QString("%1").arg(value));
}


void MusicWindow::on_btn_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
    this->player->pause();
}

