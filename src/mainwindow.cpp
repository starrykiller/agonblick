#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QTime>
#include <QCoreApplication>
#include "student.h"
#include <QMessageBox>

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    //conf.par=&Ui::mainWindow;
    if (!conf.read()) {
        QMessageBox::critical(this, "错误", "(-1) 配置文件无法打开，请检查配置文件是否存在");
        exit(-1);
    }
}

mainWindow::~mainWindow()
{
    delete ui;

}


void mainWindow::on_exit_clicked()
{
    exit(0);
}


void mainWindow::on_random_clicked()
{
    ui->random->setDisabled(true);
    // started random
    int times = QRandomGenerator::global()->bounded(7,20);
    int sleepMS = QRandomGenerator::global()->bounded(50,100);
    for (int i = 0; i < times; i ++) {
        student st = conf.rander[QRandomGenerator::global()->bounded(0,44)];
        ui->nameShow->setHtml("<span style='font-family: consolas, 方正小标宋简体, 华文中宋, 微软雅黑; font-weight: 300; font-size: 40pt;'>" +
                              QString::number(st.getId()) + "=>" + st.getName() + "</span>");
        Sleep(sleepMS);
    }
    ui->random->setDisabled(false);
}

void mainWindow::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
