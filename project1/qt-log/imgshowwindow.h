#ifndef IMGSHOWWINDOW_H
#define IMGSHOWWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QPixmap>
namespace Ui {
class ImgShowWindow;
}

class ImgShowWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImgShowWindow(QWidget *parent = nullptr);
    ~ImgShowWindow();



private slots:
    void on_btn_file_clicked();

    void on_btn_file_triggered(QAction *arg1);

    void on_list_file_itemDoubleClicked(QListWidgetItem *item);

    void on_btn_pre_clicked();

    void on_btn_next_clicked();

    void on_btn_enlarge_clicked();

    void on_btn_reduce_clicked();

    void on_btn_left_clicked();

    void on_btn_right_clicked();

    void on_btn_delete_clicked();

    void on_btn_return_clicked();

private:
    Ui::ImgShowWindow *ui;
};

#endif // IMGSHOWWINDOW_H
