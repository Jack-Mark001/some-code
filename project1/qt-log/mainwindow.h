#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "indexwindow.h"
#include "registwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void sendName(QString name);

private slots:
    void on_btn_log_clicked();

    void on_btn_reg_clicked();

    void redata(QString acc,QString pwd);

private:
    Ui::MainWindow *ui;
    IndexWindow *indexw;
    registWindow *registw;

};
#endif // MAINWINDOW_H
