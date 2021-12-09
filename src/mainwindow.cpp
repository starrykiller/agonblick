#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator64>
#include <QTime>
#include <QCoreApplication>
#include "student.h"
#include <QMessageBox>
#include <QString>
#include <QGraphicsBlurEffect>
#include <QMouseEvent>

const QString __VER__ = "1.6.0";

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    ui->kill->installEventFilter(this);
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
    int times = QRandomGenerator64::global()->bounded(7,20);
    int sleepMS = QRandomGenerator64::global()->bounded(50,70);
    student st;
    for (int i = 0; i < times; i ++) {
        int id;
        do
            id = (QRandomGenerator64::global()->bounded(0,1919810) % 114514 +
                  QTime::currentTime().msec() % 114514) % conf.num;
        while (!(id >= 0 && id < conf.num));
        st = conf.students[id];
        ui->nameShow->setHtml(returnHtml(st));
        Sleep(sleepMS);
    }

    if (st.getName().indexOf("陈鸿") != -1 && QRandomGenerator64::global()->bounded(0, 5) >= 3) { // 40%
        ui->nameShow->setHtml(startHtml +  "(" + st.getId() +
                              ") <span style=\"color: rgb(0, 255, 0);\"><b>东鸟民</b></span>" + endHtml);
        ui->kill->setText("#1(");
    }
    if (nextMQCP == true) {
        nextMQCP = false;
        ui->nameShow->setHtml(returnHtml(student("莫仇", 0), 255, 0, 153));
    }
    else {
        // 3%几率
        if (QRandomGenerator64::global()->bounded(0,100)<=3) {
            nextMQCP = false;
            ui->nameShow->setHtml(returnHtml(student("莫仇", 0), 255, 0, 153));
        }
    }
    if (!lastMQ && last.getId()==5&& QRandomGenerator64::global()->bounded(0, 10) > 0) {
        ui->nameShow->setHtml(returnHtml(conf.students[3]));
        st=conf.students[3];
        //ui->kill->setText("#4&#5");
        lastMQ=true;
    }
    else if (!lastMQ && last.getId()==4&& QRandomGenerator64::global()->bounded(0, 10) > 0) {
        ui->nameShow->setHtml(returnHtml(conf.students[4]));
        st=conf.students[4];
        //ui->kill->setText("#4&#5");
        lastMQ=true;
    }
    else lastMQ=false;
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

QString mainWindow::returnHtml(student st, int r, int g, int b) {
    QString Id;
    if (st.getId() < 10) Id = "0" + QString::number(st.getId());
    else Id = QString::number(st.getId());
    return startHtml + "[" + Id + "]:<span style=\"color: rgb("  + QString::number(r) +
            ", " + QString::number(g) + "," + QString::number(b) + ");\"><b>" + st.getName() + "</b></span>" + endHtml;
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
    int times = QRandomGenerator64::global()->bounded(7,20);
    int sleepMS = QRandomGenerator64::global()->bounded(50,70);
    for (int i = 0; i < times; i ++) {
        group gp = conf.groups[QRandomGenerator64::global()->bounded(0,int(conf.groupNum))];
        ui->nameShow->setHtml(returnHtmlByGroup(gp));
        Sleep(sleepMS);
    }
    ui->random->setDisabled(false);
    ui->randomByGroup->setDisabled(false);
}

bool mainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->kill)
    {

        //判断事件
        if(event->type() == QEvent::MouseButtonPress)
        {
            this->nextMQCP = true;
            return true; //该事件已处理
        }
        else
        {
            return false; //如果是其它事件，可以进行进一步的处理
        }
    }
    else
    {
        return QWidget::eventFilter(watched, event);
    }
}
