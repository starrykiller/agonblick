#include "ui/mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QRandomGenerator>
#include <QMutex>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/icon.ico"));
    QFontDatabase::addApplicationFont(":/font/FZSJ-RUFSYXK.TTF");
    mainWindow w;

    w.show();
    return a.exec();
}

