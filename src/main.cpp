#include "mainwindow.h"
#include <QIcon>
#include <QApplication>
#include <QRandomGenerator>
#include <QPalette>
#include <QPixmap>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/icon.ico"));
    QFontDatabase::addApplicationFont(":/font/FZSJ-RUFSYXK.TTF");
    mainWindow w;
    int bg = QRandomGenerator::global()->bounded(1,3);
    QPixmap pixmap;
        if (bg == 1)
            pixmap = QPixmap(":/bg/1.png").scaled(w.size());

        else if (bg == 2)
            pixmap = QPixmap(":/bg/2.png").scaled(w.size());
        else
            pixmap = QPixmap(":/bg/3.png").scaled(w.size());

      QPalette palette(w.palette());

      palette.setBrush(w.backgroundRole(), QBrush(pixmap));

      w.setPalette(palette);
    w.show();
    return a.exec();
}
