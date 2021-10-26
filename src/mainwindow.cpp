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
    ui->nameShow->setHtml(startHtml+"成功读取"+QString::number(conf.num)+"人" +endHtml);
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
    student st;
    for (int i = 0; i < times; i ++) {
        st = conf.rander[QRandomGenerator::global()->bounded(0,int(conf.num - 1))];
        ui->nameShow->setHtml(returnHtml(st));
        Sleep(sleepMS);
    }
    if (st==last) {
        ui->kill->setText("Double Kill!");
    }
    else ui->kill->setText("");
    last=st;
    ui->random->setDisabled(false);
}

void mainWindow::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString mainWindow::returnHtml(student st) {
    QString Id;
    if (st.getId() < 10) Id = "0" + QString::number(st.getId());
    else Id = QString::number(st.getId());
    return startHtml + "[" + Id + "]:" + st.getName() + endHtml;
}
