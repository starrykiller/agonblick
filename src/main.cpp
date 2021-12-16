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
    int bg = QRandomGenerator::global()->bounded(0, 100) % 4 + 1;

    w.show();
    return a.exec();
}
