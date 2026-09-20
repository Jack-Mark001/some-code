#include "videowindow.h"
#include "ui_videowindow.h"
#include <QNetworkReply>

VideoWindow::VideoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VideoWindow)
{
    ui->setupUi(this);

    ui->btn_play->setProperty("mode","play");

    this->initPlayer();
    this->initNetList();

    connect(this->player,&QMediaPlayer::durationChanged,this,&VideoWindow::durationChanged);
    connect(this->player,&QMediaPlayer::positionChanged,this,&VideoWindow::positionChanged);

    connect(this->player, &QMediaPlayer::mediaStatusChanged,this, &VideoWindow::onMediaStatusChanged);

    ui->label_now->setText("00:00:00");
    this->output->setVolume(1.0);
}

VideoWindow::~VideoWindow()
{
    delete ui;
}

//初始化video位置
void VideoWindow::initPlayer()
{

    this->player=new QMediaPlayer(this);
    this->output=new QAudioOutput(this);
    this->videoWid=new QVideoWidget(this);

    this->player->setVideoOutput(this->videoWid);
    this->player->setAudioOutput(this->output);

    ui->video_window->addWidget(this->videoWid);

    ui->volume_bar->setValue(100);
    this->output->setVolume(ui->volume_bar->value()/100);
    ui->volume->setText("100");

    //安装事件过滤器
    this->videoWid->installEventFilter(this);

}

void VideoWindow::initNetList()
{
    this->manager=new QNetworkAccessManager(this);
    connect(this->manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
        QByteArray data=reply->readAll();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if(doc.isObject()){
            QJsonObject obj=doc.object();
            int code=obj.value("code").toInt();
            bool success=obj.value("success").toBool();
            if(code==200&&success){
                QJsonArray arr=obj.value("data").toArray();
                for (int i = 0; i < arr.size(); ++i) {

                    QJsonObject o=arr.at(i).toObject();

                    QListWidgetItem *item=new QListWidgetItem;
                    item->setText(o.value("name").toString());
                    item->setData(Qt::UserRole,o.value("path").toString());

                    ui->online_list->addItem(item);
                }
                ui->online_list->setCurrentRow(0);
                this->player->setSource(arr.at(0).toObject().value("path").toString());

            }
        }
    });

    //发起请求
    this->manager->get(QNetworkRequest(QUrl("http://localhost/videoList.json")));

}

bool VideoWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == videoWid && event->type() == QEvent::MouseButtonDblClick)
    {
        // // qDebug() << "double click.............";
        // // 把videoWidget变回为子窗口

        // this->videoWid->setWindowFlags(Qt::SubWindow);
        // // 退出全屏
        // this->videoWid->showNormal();

        if (m_isVideoFullScreen)
        {
            // 当前是全屏 -> 退出全屏
            videoWid->setWindowFlags(Qt::SubWindow);
            videoWid->showNormal();
            m_isVideoFullScreen = false;
        }
        else
        {
            // 当前是普通窗口 -> 进入全屏
            videoWid->setWindowFlags(Qt::Window);
            videoWid->showFullScreen();
            m_isVideoFullScreen = true;
        }
        return true; // 阻隔事件，不再传递
    }
    // 处理esc
    // 注意:键盘事件,必须要先把QEvent转换为QKeyEvent,再拿到键盘的按键
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Escape)
        {
            qDebug() << "按下了esc.............";
            // 把videoWidget变回为子窗口
            this->videoWid->setWindowFlags(Qt::SubWindow);
            // 退出全屏
            this->videoWid->showNormal();
        }
    }

    return QObject::eventFilter(object,event);

}

void VideoWindow::on_btn_play_clicked()
{
    if(ui->online_list->count()==0){
        QMessageBox::warning(this,"警告","无播放源，在服务器添加视频后观看");
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


void VideoWindow::on_online_list_itemDoubleClicked(QListWidgetItem *item)
{
    //拿到路径
    QString path=item->data(Qt::UserRole).toString();

    this->player->setSource(QUrl::fromLocalFile(path));


    this->player->play();
    ui->btn_play->setProperty("mode","pause");

    ui->btn_play->style()->unpolish(ui->btn_play);
    ui->btn_play->style()->polish(ui->btn_play);
    ui->btn_play->update();
}


void VideoWindow::on_btn_pre_clicked()
{
    int index=0;

    index=ui->online_list->currentRow();
    if(index==0){
        index=ui->online_list->count()-1;
    }else{
        index--;
    }
    ui->online_list->setCurrentRow(index);
    this->on_online_list_itemDoubleClicked(ui->online_list->currentItem());
}


void VideoWindow::on_btn_next_clicked()
{
    int index=0;

    index=ui->online_list->currentRow();
    if(index==ui->online_list->count()-1){
        index=0;
    }else{
        index++;
    }
    ui->online_list->setCurrentRow(index);
    this->on_online_list_itemDoubleClicked(ui->online_list->currentItem());

}


void VideoWindow::on_progress_bar_sliderReleased()
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

void VideoWindow::durationChanged(int duration)
{
    ui->progress_bar->setMaximum(duration);

    QTime time(0,0,0);
    time=time.addMSecs(duration);

    QString t=time.toString("HH:mm:ss");

    ui->label_all->setText(t);
}

void VideoWindow::positionChanged(int position)
{
    if(!ui->progress_bar->isSliderDown()){
        ui->progress_bar->setValue(position);
    }


    QTime time(0,0,0);
    time=time.addMSecs(position);

    QString t=time.toString("HH:mm:ss");

    ui->label_now->setText(t);

    // updateLyricDisplay(position);

}


void VideoWindow::on_btn_full_clicked()
{
    this->videoWid->setWindowFlag(Qt::Window);

    this->videoWid->showFullScreen();
}

void VideoWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        this->on_btn_next_clicked();
    }
}


void VideoWindow::on_volume_bar_valueChanged(int value)
{
    float v=value/100.0f;

    this->output->setVolume(v);

    ui->volume->setText(QString("%1").arg(value));
}


void VideoWindow::on_btn_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
    this->player->pause();
}

