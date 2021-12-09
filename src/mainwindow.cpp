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
#include <QBitmap>
#include <QPainter>
#include <QDebug>

const QString __VER__ = "2.0.0";

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    ui->statusShow->installEventFilter(this);
// 设置圆角
    QBitmap bmp(this->size());

        bmp.fill();

        QPainter p(&bmp);
        p.setRenderHint(QPainter::Antialiasing);

        p.setPen(Qt::NoPen);

        p.setBrush(Qt::black);


        p.drawRoundedRect(bmp.rect(),20,20);

        setMask(bmp);
    ui->nameShow->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->statusShow->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //conf.par=&Ui::mainWindow;
    if (!conf.read()) {
        QMessageBox::critical(this, "错误", "(-1) 配置文件无法打开，请检查配置文件是否存在");
        exit(-1);
    }
    ui->nameShow->setHtml(startHtml+QString::number(conf.num)+";" + QString::number(conf.groupNum) +endHtml);
    setWindowTitle("Agonblick [" + __VER__ + "] " + __DATE__ + " " + __TIME__);
    ui->infoShow->setText("Agonblick [v" + __VER__ + "] 编译于" + __DATE__ + " " + __TIME__);
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
    ui->statusShow->setText("");
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
        ui->nameShow->setHtml(returnHtml(st, 255, 0, 255));
        Sleep(sleepMS);
    }

    if (st.getName().indexOf("陈鸿") != -1 && QRandomGenerator64::global()->bounded(0, 5) >= 3) { // 40%
        ui->nameShow->setHtml(startHtml +  "(" + st.getId() +
                              ") <span style=\"color: rgb(0, 255, 0);\" font-family=如风似月行楷;><b>东鸟民</b></span>" + endHtml);
        ui->statusShow->setText("#1(");
    }
    // 2%几率
    if (QRandomGenerator64::global()->bounded(0,100)<=1) {
            nextMQCP = false;
            ui->nameShow->setHtml(returnHtml(student("莫仇", 0), 255, 0, 153));
        }

    else if (!lastMQ && last.getId()==5&& QRandomGenerator64::global()->bounded(0, 10) > 3) {
        ui->nameShow->setHtml(returnHtml(conf.students[3]));
        st=conf.students[3];
        //ui->statusShow->setText("#4&#5");
        lastMQ=true;
    }
    else if (!lastMQ && last.getId()==4&& QRandomGenerator64::global()->bounded(0, 10) > 3) {
        ui->nameShow->setHtml(returnHtml(conf.students[4]));
        st=conf.students[4];
        //ui->statusShow->setText("#4&#5");
        lastMQ=true;
    }
    else lastMQ=false;


    if (!lastGC && last.getId()==20&& QRandomGenerator64::global()->bounded(0, 10) > 2) {
        ui->nameShow->setHtml(returnHtml(conf.students[22-1]));
        st=conf.students[22-1];
        //ui->statusShow->setText("#4&#5");
        lastGC=true;
    }
    else if (!lastGC && last.getId()==22&& QRandomGenerator64::global()->bounded(0, 10) > 2) {
        ui->nameShow->setHtml(returnHtml(conf.students[20-1]));
        st=conf.students[20-1];
        //ui->statusShow->setText("#4&#5");
        lastGC=true;
    }
    else lastGC=false;

    if (QRandomGenerator64::global()->bounded(0,100)<=1) {
            nextMQCP = false;
            ui->nameShow->setHtml(returnHtml(student("莫仇", 0), 255, 0, 153));
        }

    if (st==last) {
        ui->statusShow->setText("Double Kill!");
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
            ", " + QString::number(g) + "," + QString::number(b) + "); font-family: 如风似月行楷;\"><b>" + st.getName() + "</b></span>" + endHtml;
}

QString mainWindow::returnHtmlByGroup(group gp) {
    QString Id = QString::number(gp.getId());
    return startHtml + "[" + Id + "] <span style=\"color: rgb(0, 204, 0); font-family: 如风似月行楷;\"><b>" + gp.getLeaderName() + "</b>组</span>" + endHtml;
}

void mainWindow::on_randomByGroup_clicked()
{
    ui->random->setDisabled(true);
    ui->randomByGroup->setDisabled(true);
    // TODO: do randoming
    ui->statusShow->setText("");
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
    if(watched == ui->statusShow)
    {

        //判断事件
        if(event->type() == QEvent::MouseButtonPress)
        {
            // this->nextMQCP = true;
            // cancel for 1.6.1
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

void mainWindow::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->pos();
    }
}
void mainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}
void mainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}


void mainWindow::on_checkBox_stateChanged(int arg1)
{
    qDebug() << ui->stayOnTop->checkState() << " " << arg1;
    this->hide();
    if (ui->stayOnTop->checkState() == true) {
        setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    }
    else {
        setWindowFlags(Qt::FramelessWindowHint);
    }
    this->show();
}


void mainWindow::on_stayOnTop_clicked()
{
    qDebug() << ui->stayOnTop->checkState();
    this->hide();
    if (ui->stayOnTop->checkState() == true) {
        setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    }
    else {
        setWindowFlags(Qt::FramelessWindowHint);
    }
    this->show();
}

