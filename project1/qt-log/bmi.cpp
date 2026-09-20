#include "bmi.h"
#include "ui_bmi.h"
#include "iostream"

BMI::BMI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BMI)
{
    ui->setupUi(this);
}

BMI::~BMI()
{
    delete ui;
}

void BMI::on_pushButton_clicked()
{
    QString hei=ui->line_hei->text();
    QString wei=ui->line_wei->text();


    float res=wei.toFloat()/std::sqrt(hei.toFloat());

    ui->label_res->setText(QString::number(res));
}


void BMI::on_pushButton_2_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

