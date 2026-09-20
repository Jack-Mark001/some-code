#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->musicwind=new MusicWindow(this);
    this->videowind=new VideoWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->musicwind->show();
    this->hide();
}


void MainWindow::on_pushButton_2_clicked()
{
    this->videowind->show();
    this->hide();
}

