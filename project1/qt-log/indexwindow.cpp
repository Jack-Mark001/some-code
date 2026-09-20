#include "indexwindow.h"
#include "ui_indexwindow.h"


IndexWindow::IndexWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IndexWindow)
{
    ui->setupUi(this);
    this->bmi=new BMI(this);

    this->img=new ImgShowWindow(this);
}

IndexWindow::~IndexWindow()
{
    delete ui;
}

void IndexWindow::on_pushButton_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void IndexWindow::on_pushButton_2_clicked()
{
    bmi->show();
    this->hide();
}

void IndexWindow::getData(QString acc)
{
    QString title=QString("欢迎 %1 成功登录系统").arg(acc);
    ui->label_name->setText(title);
}




void IndexWindow::on_btn_imgshow_clicked()
{
    img->show();
    this->hide();
}

