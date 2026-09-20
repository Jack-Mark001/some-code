#include "registwindow.h"
#include "ui_registwindow.h"

registWindow::registWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::registWindow)
{
    ui->setupUi(this);
}

registWindow::~registWindow()
{
    delete ui;
}

void registWindow::on_btn_return_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void registWindow::on_btn_regist_clicked()
{
    QString acc=ui->lineEdit_account->text();
    QString pwd=ui->lineEdit_pwd->text();
    QString repwd=ui->lineEdit_repwd->text();

    if(acc.isEmpty() || pwd.isEmpty() || repwd.isEmpty()){
        ui->label_note->setText("账号和密码不能为空!");
        ui->label_note->setStyleSheet("color:red");
        return;
    }

    if(pwd!=repwd){
        ui->label_note->setText("密码不相同!请重新输入");
        ui->label_note->setStyleSheet("color:red");
        return;
    }

    this->parentWidget()->show();
    this->hide();

    //回显数据  自定义信号和槽
    emit logdata(acc,pwd);


}

