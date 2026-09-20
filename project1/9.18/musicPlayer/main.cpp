#include "musicwindow.h"
#include "videowindow.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // VideoWindow vw;
    // vw.show();
    // MusicWindow mw;
    // mw.show();
    MainWindow w;
    w.show();
    return QApplication::exec();
}
