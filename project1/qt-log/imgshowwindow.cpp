#include "imgshowwindow.h"
#include "ui_imgshowwindow.h"

ImgShowWindow::ImgShowWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImgShowWindow)
{
    ui->setupUi(this);

    QMenu *menu = new QMenu();
    menu->addAction("打开文件");
    menu->addAction("退出");

    ui->btn_file->setMenu(menu);

}

ImgShowWindow::~ImgShowWindow()
{
    delete ui;
}

void ImgShowWindow::on_btn_file_clicked()
{
    ui->btn_file->showMenu();
}


void ImgShowWindow::on_btn_file_triggered(QAction *act)
{
    QString name=act->text();
    if(name=="打开文件"){
        //文件选择对话框
        QStringList paths= QFileDialog::getOpenFileNames(this,"选择要查看的一个或多个图片","D:/pixiv","*.jpg *.png *.jpeg");

        //判断是否选择了item
        bool isEmpty=ui->list_file->count()==0 ? true:false;
        for(QString path:paths){

            QFileInfo fileinfo(path);
            //每次遍历创建一个item对象

            QListWidgetItem *item=new QListWidgetItem;
            item->setText(fileinfo.fileName());//设置列表条目名
            item->setData(Qt::UserRole,path);

            ui->list_file->addItem(item);


        }

        if(isEmpty){
            ui->list_file->setCurrentRow(0);
            this->on_list_file_itemDoubleClicked(ui->list_file->currentItem());
        }

    }else if(name=="退出"){
        QMessageBox::StandardButton res= QMessageBox::question(this,"警告","是否退出查看器");
        if(res==QMessageBox::Yes){
            exit(EXIT_SUCCESS);
        }
    }
}


void ImgShowWindow::on_list_file_itemDoubleClicked(QListWidgetItem *item)
{
    //获取路径，然后map展示图片
    QString path=item->data(Qt::UserRole).toString();

    QPixmap map(path);

    //图片自适应
    map = map.scaled(ui->show->size(),
                     Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);

    ui->show->setPixmap(map);
}


void ImgShowWindow::on_btn_pre_clicked()
{
    int index= ui->list_file->currentRow();

    if(index==0){
        index=ui->list_file->count()-1;
    }else{
        index--;
    }

    ui->list_file->setCurrentRow(index);

    this->on_list_file_itemDoubleClicked(ui->list_file->currentItem());

}


void ImgShowWindow::on_btn_next_clicked()
{
    int index= ui->list_file->currentRow();

    if(index==ui->list_file->count()-1){
        index=0;
    }else{
        index++;
    }

    ui->list_file->setCurrentRow(index);

    this->on_list_file_itemDoubleClicked(ui->list_file->currentItem());

}


void ImgShowWindow::on_btn_enlarge_clicked()
{
    //获取原图高宽
    QPixmap map=ui->show->pixmap();
    int w=map.width();
    int h=map.height();

    w=w*1.1;
    h=h*1.1;
    //重新从磁盘读取图片后，在设置高宽
    QString path=ui->list_file->currentItem()->data(Qt::UserRole).toString();

    QPixmap newmap(path);
    newmap=newmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    ui->show->setPixmap(newmap);

}


void ImgShowWindow::on_btn_reduce_clicked()
{
    //获取原图高宽
    QPixmap map=ui->show->pixmap();
    int w=map.width();
    int h=map.height();

    w=w*0.9;
    h=h*0.9;
    //重新从磁盘读取图片后，在设置高宽
    QString path=ui->list_file->currentItem()->data(Qt::UserRole).toString();

    QPixmap newmap(path);
    newmap=newmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    ui->show->setPixmap(newmap);
}


void ImgShowWindow::on_btn_left_clicked()
{
    QPixmap map=ui->show->pixmap();
    QTransform tf;
    tf.rotate(-90);
    map=map.transformed(tf,Qt::SmoothTransformation);
    ui->show->setPixmap(map);
}


void ImgShowWindow::on_btn_right_clicked()
{
    QPixmap map=ui->show->pixmap();
    QTransform tf;
    tf.rotate(90);
    map=map.transformed(tf,Qt::SmoothTransformation);
    ui->show->setPixmap(map);
}


void ImgShowWindow::on_btn_delete_clicked()
{
    if(ui->list_file->count()==0 ){
        QMessageBox::critical(this,"警告","没有内容删啥");
        return;
    }

    //有图片  删除是take  要删除item

    ui->list_file->takeItem(ui->list_file->currentRow());

    if(ui->list_file->count()==0){
        ui->show->clear();

    }else{
        this->on_list_file_itemDoubleClicked(ui->list_file->currentItem());

    }
}



void ImgShowWindow::on_btn_return_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

