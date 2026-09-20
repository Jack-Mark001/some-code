#ifndef INDEXWINDOW_H
#define INDEXWINDOW_H

#include <QMainWindow>
#include "bmi.h"
#include "imgshowwindow.h"

namespace Ui {
class IndexWindow;
}

class IndexWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IndexWindow(QWidget *parent = nullptr);
    ~IndexWindow();

public slots:
    void getData(QString acc);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_btn_imgshow_clicked();

private:
    Ui::IndexWindow *ui;
    BMI *bmi;
    ImgShowWindow *img;
};

#endif // INDEXWINDOW_H
