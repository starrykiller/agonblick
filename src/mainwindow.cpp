#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QTime>
#include <QCoreApplication>
#include "student.h"
#include <QMessageBox>
#include <QString>
#include <QGraphicsBlurEffect>

const QString __VER__ = "1.5.0";

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
    ui->nameShow->setHtml(startHtml+QString::number(conf.num)+";" + QString::number(conf.groupNum) +endHtml);
    setWindowTitle("Agonblick [" + __VER__ + "] " + __DATE__ + " " + __TIME__);
   // QGraphicsBlurEffect *eff1 = new QGraphicsBlurEffect;
    //eff1->setBlurRadius(10);
    //ui->frame->setGraphicsEffect(eff1);
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
    ui->randomByGroup->setDisabled(true);
    ui->kill->setText("");
    // started random
    int times = QRandomGenerator::global()->bounded(7,20);
    int sleepMS = QRandomGenerator::global()->bounded(50,70);
    student st;
    for (int i = 0; i < times; i ++) {
        st = conf.students[QRandomGenerator::global()->bounded(0,int(conf.num))];
        ui->nameShow->setHtml(returnHtml(st));
        Sleep(sleepMS);
    }

    if (st.getName().indexOf("陈鸿") != -1 && QRandomGenerator::global()->bounded(0, 5) >= 3) { // 40%
        ui->nameShow->setHtml(startHtml +  "(" + st.getId() +
                              ") <span style=\"color: rgb(0, 255, 0);\"><b>东鸟民</b></span>" + endHtml);
        ui->kill->setText("#1(");
    }
    /*if (last.getId()==5&& QRandomGenerator::global()->bounded(0, 10) > 0) {
        ui->nameShow->setHtml(returnHtml(conf.students[3]));
        st=conf.students[3];
        ui->kill->setText("#4&#5");
    }
    else if (last.getId()==4&& QRandomGenerator::global()->bounded(0, 10) > 0) {
        ui->nameShow->setHtml(returnHtml(conf.students[4]));
        st=conf.students[4];
        ui->kill->setText("#4&#5");
    }*/
    if (st==last) {
        ui->kill->setText("Double Kill! (0.04%)");
    }
    last=st;
    ui->random->setDisabled(false);
    ui->randomByGroup->setDisabled(false);
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
    return startHtml + "[" + Id + "]:<span style=\"color: rgb(0, 75, 255);\"><b>" + st.getName() + "</b></span>" + endHtml;
}

QString mainWindow::returnHtmlByGroup(group gp) {
    QString Id = QString::number(gp.getId());
    return startHtml + "[" + Id + "] <span style=\"color: rgb(255, 125, 0);\"><b>" + gp.getLeaderName() + "</b>组</span>" + endHtml;
}

void mainWindow::on_randomByGroup_clicked()
{
    ui->random->setDisabled(true);
    ui->randomByGroup->setDisabled(true);
    // TODO: do randoming
    ui->kill->setText("");
    // started random
    int times = QRandomGenerator::global()->bounded(7,20);
    int sleepMS = QRandomGenerator::global()->bounded(50,70);
    for (int i = 0; i < times; i ++) {
        group gp = conf.groups[QRandomGenerator::global()->bounded(0,int(conf.groupNum))];
        ui->nameShow->setHtml(returnHtmlByGroup(gp));
        Sleep(sleepMS);
    }
    ui->random->setDisabled(false);
    ui->randomByGroup->setDisabled(false);
}

