#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->indexw=new IndexWindow(this);

    this->registw=new registWindow(this);

    connect(this->registw,&registWindow::logdata,this,&MainWindow::redata);
    connect(this,&MainWindow::sendName,this->indexw,&IndexWindow::getData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_log_clicked()
{
    QString acc=ui->line_account->text();
    QString pwd=ui->line_pwd->text();

    qDebug()<<acc<<"   "<<pwd;

    if(acc.isEmpty()||pwd.isEmpty()){
        ui->label_note->setText("注意：密码和账号不能为空！！");
        ui->label_note->setStyleSheet("color:red");
        return;
    }

    if(acc=="admin" && pwd=="123"){
        ui->label_note->setText("登录成功");
        this->indexw->show();
        this->hide();
        emit sendName(acc);

    }else{
        ui->label_note->setText("注意：账号密码错误！");
        ui->label_note->setStyleSheet("color:red");
    }

}


void MainWindow::on_btn_reg_clicked()
{
    this->registw->show();
    this->hide();
}

void MainWindow::redata(QString acc, QString pwd)
{
    ui->line_account->setText(acc);
    ui->line_pwd->setText(pwd);
}





