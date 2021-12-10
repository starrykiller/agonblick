#include "mainwindow.h"
#include "student.h"
#include "ui_mainwindow.h"
#include <QBitmap>
#include <QCoreApplication>
#include <QCursor>
#include <QDebug>
#include <QGraphicsBlurEffect>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QRandomGenerator64>
#include <QString>
#include <QTime>

const QString __VER__ = "3.2.1";

mainWindow::mainWindow(QWidget* parent)
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

    p.drawRoundedRect(bmp.rect(), 20, 20);

    setMask(bmp);
    ui->nameShow->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->statusShow->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    // conf.par=&Ui::mainWindow;
    if (!conf.read()) {
        QMessageBox::critical(this, "致命错误", conf.ParseError);
        exit(-1);
    }
    ui->nameShow->setHtml(startHtml + QString::number(conf.num) + ";" + QString::number(conf.groupNum) + ";" + QString::number(conf.cpNum) + endHtml);
    setWindowTitle("Agonblick [" + __VER__ + "] " + __DATE__ + " " + __TIME__);
    ui->infoShow->setText("Agonblick [v" + __VER__ + "] 编译于" + __DATE__ + " " + __TIME__);
    // QGraphicsBlurEffect *eff1 = new QGraphicsBlurEffect;
    // eff1->setBlurRadius(10);
    // ui->frame->setGraphicsEffect(eff1);
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
    int times = QRandomGenerator64::global()->bounded(7, 20);
    int sleepMS = QRandomGenerator64::global()->bounded(50, 70);
    student st;
    for (int i = 0; i < times; i++) {
        int id;
        do
            id = (QRandomGenerator64::global()->bounded(0, 1919810) % 114514 + QTime::currentTime().msec() % 114514) % conf.num;
        while (!(id >= 0 && id < int(conf.num)));
        st = conf.students[id];
        ui->nameShow->setHtml(returnHtml(st, 255, 0, 255));
        Sleep(sleepMS);
    }

    if (st.getName().indexOf("陈鸿") != -1 && QRandomGenerator64::global()->bounded(0, 5) >= 3) { // 40%
        ui->nameShow->setHtml(startHtml + "(" + st.getId() + ") <span style=\"color: rgb(0, 255, 0);\" "
                                                             "font-family=如风似月行楷;><b>东鸟民</b></span>"
            + endHtml);
        ui->statusShow->setText("#1(");
    }

    if (QRandomGenerator64::global()->bounded(0, 1000) <= int(150 > conf.cpNum * 3 ? conf.cpNum * 30 : 150)) {
        // 设有n对cp，
        // 则概率为3n% (当3n<15),
        // 15% (3n>=15)
        int randomedCP = QRandomGenerator64::global()->bounded(0, int(conf.cpNum));
        ui->nameShow->setHtml(returnHtmlByCP(conf.cps[randomedCP]));
        st = student(conf.cps[randomedCP].cpName, conf.cps[randomedCP].cpId);
    } else if (QRandomGenerator64::global()->bounded(0, 1000) <= 750 && cnt > 0) {
        // 75%：CP两人互相抽中
        for (unsigned int i = 0; i < conf.cpNum; i++) {
            if (his[cnt - 1] == conf.cps[i].cp1) {
                st = conf.cps[i].cp2;
                break;
            } else if (his[cnt - 1] == conf.cps[i].cp2) {
                st = conf.cps[i].cp1;
                break;
            }
        }
    }

    his.append(st);
    last = st;
    cnt++;

    // 检查combo
    int combo = 1, randomedTimes = 1, flag = true;
    // 是否连起来？
    if (cnt > 1) {
        for (int i = cnt - 2; i >= 0; i--) {
            if (his[i] == st) {
                randomedTimes++;
                if (flag)
                    combo++;
            } else
                flag = false;
        }
    }
    if (randomedTimes > 1) {
        if (combo > 1)
            ui->statusShow->setText("Total " + QString::number(randomedTimes) + "; Combo " + QString::number(combo));
        else
            ui->statusShow->setText("Total " + QString::number(randomedTimes));
    }

    ui->random->setDisabled(false);
    ui->randomByGroup->setDisabled(false);
}

void mainWindow::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString mainWindow::returnHtml(student st)
{
    QString Id;
    if (st.getId() < 10)
        Id = "0" + QString::number(st.getId());
    else
        Id = QString::number(st.getId());
    return startHtml + "[" + Id + "]:<span style=\"color: rgb(0, 75, 255);\"><b>" + st.getName() + "</b></span>" + endHtml;
}

QString mainWindow::returnHtml(student st, int r, int g, int b)
{
    QString Id;
    if (st.getId() < 10)
        Id = "0" + QString::number(st.getId());
    else
        Id = QString::number(st.getId());
    return startHtml + "[" + Id + "]:<span style=\"color: rgb(" + QString::number(r) + ", " + QString::number(g) + "," + QString::number(b) + "); font-family: 如风似月行楷;\"><b>" + st.getName() + "</b></span>" + endHtml;
}

QString mainWindow::returnHtmlByGroup(group gp)
{
    QString Id = QString::number(gp.getId());
    return startHtml + "[" + Id + "] <span style=\"color: rgb(0, 204, 0); font-family: "
                                  "如风似月行楷;\"><b>"
        + gp.getLeaderName() + "</b>组</span>" + endHtml;
}

QString mainWindow::returnHtmlByCP(cp CP)
{
    QString Id = QString::number(CP.cpId);
    return startHtml + "[" + Id + "] <span style=\"color: rgb(102, 0, 204); font-family: "
                                  "如风似月行楷;\"><b>"
        + CP.cpName + "</b></span>" + endHtml;
}

void mainWindow::on_randomByGroup_clicked()
{
    ui->random->setDisabled(true);
    ui->randomByGroup->setDisabled(true);
    // TODO: do randoming
    ui->statusShow->setText("");
    // started random
    int times = QRandomGenerator64::global()->bounded(7, 20);
    int sleepMS = QRandomGenerator64::global()->bounded(50, 70);
    for (int i = 0; i < times; i++) {
        group gp = conf.groups[QRandomGenerator64::global()->bounded(
            0, int(conf.groupNum))];
        ui->nameShow->setHtml(returnHtmlByGroup(gp));
        Sleep(sleepMS);
    }
    ui->random->setDisabled(false);
    ui->randomByGroup->setDisabled(false);
}

bool mainWindow::eventFilter(
    QObject* watched,
    QEvent*
        event)
{ /*
     if(watched == ui->random || watched == ui->randomByGroup ||
     watched == ui->exit)
     {
         //判断事件
         if(event->type() == QEvent::MouseButtonPress )
         {
             // this->nextMQCP = true;
             // cancel for 1.6.1
             m_move = true;
             //记录鼠标的世界坐标.
             m_startPoint = QCursor::pos();
             qDebug() << m_startPoint;
             //m_startPoint = event->pos();
             //记录窗体的世界坐标.
             m_windowPoint = this->frameGeometry().topLeft();
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
     }*/
    return true;
}

void mainWindow::mousePressEvent(QMouseEvent* event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton) {
        // if (event->globalPos())
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        // qDebug() << m_startPoint;
        // m_startPoint = event->pos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}
void mainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        // (1130, 1132)
        //
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        // QPoint relativePos = event->pos() - m_startPoint;
        // QPoint relativePos = event->globalPos();
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos);
    }
}
void mainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        //改变移动状态.
        m_move = false;
    }
}

void mainWindow::on_stayOnTop_stateChanged(int arg1)
{
    this->hide();
    if (arg1 == Qt::Unchecked) {
        setWindowFlags(Qt::FramelessWindowHint);
    } else {
        setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    }
    this->show();
}

void mainWindow::on_random_pressed()
{
    if (m_move)
        return;
    m_move = true;
    //记录鼠标的世界坐标.
    m_startPoint = QCursor::pos();
    // qDebug() << m_startPoint;
    // m_startPoint = event->pos();
    //记录窗体的世界坐标.
    m_windowPoint = this->frameGeometry().topLeft();
}

void mainWindow::on_randomByGroup_pressed()
{
    if (m_move)
        return;
    m_move = true;
    //记录鼠标的世界坐标.
    m_startPoint = QCursor::pos();
    // qDebug() << m_startPoint;
    // m_startPoint = event->pos();
    //记录窗体的世界坐标.
    m_windowPoint = this->frameGeometry().topLeft();
}

void mainWindow::on_exit_pressed()
{
    if (m_move)
        return;
    m_move = true;
    //记录鼠标的世界坐标.
    m_startPoint = QCursor::pos();
    // qDebug() << m_startPoint;
    // m_startPoint = event->pos();
    //记录窗体的世界坐标.
    m_windowPoint = this->frameGeometry().topLeft();
}
