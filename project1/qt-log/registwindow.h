#ifndef REGISTWINDOW_H
#define REGISTWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class registWindow;
}

class registWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit registWindow(QWidget *parent = nullptr);
    ~registWindow();

signals:
    void logdata(QString acc,QString pwd);

private slots:
    void on_btn_return_clicked();

    void on_btn_regist_clicked();

private:
    Ui::registWindow *ui;
};

#endif // REGISTWINDOW_H
