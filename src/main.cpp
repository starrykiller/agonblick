#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QRandomGenerator>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/icon.ico"));
    QFontDatabase::addApplicationFont(":/font/FZSJ-RUFSYXK.TTF");
    mainWindow w;
    int bg = QRandomGenerator::global()->bounded(0, 8);
    QPixmap pixmap;
    if (bg <= 2)
        pixmap = QPixmap(":/bg/1.png").scaled(w.size());

    else if (bg <= 3)
        pixmap = QPixmap(":/bg/2.png").scaled(w.size());
    else if (bg <= 5)
        pixmap = QPixmap(":/bg/3.png").scaled(w.size());
    else
        pixmap = QPixmap(":/bg/4.png").scaled(w.size());

    QPalette palette(w.palette());

    palette.setBrush(w.backgroundRole(), QBrush(pixmap));

    w.setPalette(palette);
    w.show();
    return a.exec();
}
