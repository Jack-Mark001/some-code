#ifndef BMI_H
#define BMI_H

#include <QMainWindow>

namespace Ui {
class BMI;
}

class BMI : public QMainWindow
{
    Q_OBJECT

public:
    explicit BMI(QWidget *parent = nullptr);
    ~BMI();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::BMI *ui;
};

#endif // BMI_H
