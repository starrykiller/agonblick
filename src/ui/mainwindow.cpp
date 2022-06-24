#include "mainwindow.h"
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
#include <QMutex>

#include "starrywindow.h"
#include "../utility/student.h"

const QString __VER__ = "4.0.0-alpha3";

inline QString retHTML(QString s) {
    return "<span style=\"font-family: '如风似月行楷', '微软雅黑'; font-size: 24px;\">"+s+"</span>";
}

mainWindow* mainWindow::window;

mainWindow::mainWindow(QWidget* parent)
    : starryWindow()
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    window=this;
    qInstallMessageHandler(LogMessage);
    updateBorderRadius();
    ui->statusShow->installEventFilter(this);
    QVector<QString> pic;
    for (int i = 1; i <= 4; i ++) {
        pic.append(":/bg/" + QString::number(i) + ".png");
    }
    addBackground(pic);
    logw.addBackground(pic);
    logw.updateBorderRadius();

    ui->nameShow->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->statusShow->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    logw.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    if (!conf.read()) {
        ui->random->setDisabled(true);
        ui->randomByGroup->setDisabled(true);
        ui->showLog->setDisabled(true);
        ui->nameShow->setHtml(startHtml + "配置读取错误" + endHtml);
        qDebug() << "[Fatal] 致命错误:" << conf.ParseError;

        logw.move(this->frameGeometry().topRight()+QPoint(7,0));
        logw.setVisible(true);
    }
    else {
        ui->nameShow->setHtml(startHtml + QString::number(conf.num) + ";" +
                              QString::number(conf.groupNum) + ";" +
                              QString::number(conf.cpNum) + endHtml);
        setWindowTitle("Agonblick [" + __VER__ + "] " + __DATE__ + " " + __TIME__);
        ui->infoShow->setText("Agonblick [v" + __VER__ + "] 编译于" + __DATE__ + " " + __TIME__);
qDebug()<<"Agonblick [" + __VER__ + "] " + __DATE__ + " " + __TIME__;
        if (__VER__.indexOf("beta") != -1 || __VER__.indexOf("alpha") != -1) {
            ui->betaShow->setText("测试版本可能不稳定");
    }
}
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::on_exit_clicked()
{
    qDebug() << "Exiting!";
    exit(0);
}

void mainWindow::on_random_clicked()
{
    ui->random->setDisabled(true);
    ui->randomByGroup->setDisabled(true);
    ui->statusShow->setText("");
    // started random
    int times = QRandomGenerator64::global()->bounded(10, 11);
    int sleepMS = 30;
    student st;
    qDebug() << "SleepTime:" << sleepMS;
    qDebug() << "Times:" << times;
    for (int i = 0; i < times; ++i) {
        int id = QRandomGenerator64::global()->bounded(0, int(conf.num));
        st = conf.students[id];
        ui->nameShow->setHtml(returnHtml(st, 255, 0, 255));
        //qDebug() << "[" + QString::number(conf.students[id].getId()) + "]" <<
        //    conf.students[id].getName();
        Sleep(sleepMS);
    }
    if (st.getName().indexOf("陈鸿") != -1 && QRandomGenerator64::global()->bounded(0, 5) >= 3) { // 40%
        ui->nameShow->setHtml(startHtml + "(" + QString::number(st.getId()) + ") <span style=\"color: rgb(0, 255, 0);\" "
                                                             "font-family=如风似月行楷;><b>东鸟民</b></span>"
            + endHtml);
        ui->statusShow->setText(retHTML("#1("));
    }
    /*if (QRandomGenerator64::global()->bounded(0, 1000) <= int(150 > conf.cpNum * 50 ? conf.cpNum * 50 : 150)) {
        // 设有n对cp，
        // 则概率为5n% (当3n<15),
        // 15% (3n>=15)
        int randomedCP = QRandomGenerator64::global()->bounded(0, int(conf.cpNum));
        ui->nameShow->setHtml(returnHtmlByCP(conf.cps[randomedCP]));
        st = student(conf.cps[randomedCP].cpName, conf.cps[randomedCP].cpId);
        qDebug() << "[?]" << conf.cps[randomedCP].cpName;
    }
    else if (QRandomGenerator64::global()->bounded(0, 1000) <= 750 && cnt > 0) {
        // 75%：CP两人互相抽中
        for (unsigned int i = 0; i < conf.cpNum; i++) {
            if (his[cnt - 1] == conf.cps[i].cp1) {
                if (cnt>1&&his[cnt-2]==conf.cps[i].cp2) break;
                st = conf.cps[i].cp2;
                qDebug() << "[!]" << conf.cps[i].cp1.getName() << "->" << st.getName() << "(75%)";
                break;
            } else if (his[cnt - 1] == conf.cps[i].cp2) {
                if (cnt>1&&his[cnt-2]==conf.cps[i].cp1) break;
                st = conf.cps[i].cp1;
                qDebug() << "[!]" << conf.cps[i].cp2.getName() << "->" << st.getName() << "(75%)";
                break;
            }
        }
    }*/

    // 4.0.0 增加不重复功能
    if (ui->repeat->checkState()==Qt::Unchecked) {
        ui->nameShow->setHtml(returnHtml(st, 255, 0, 255));
    }
    else {
        int cnt=0; bool ok=true;

        while (st.count>0) {
            ui->statusShow->setText(retHTML("重复保护生效"));
            qDebug()<<"触发重复保护";
            int id = QRandomGenerator64::global()->bounded(0, int(conf.num));
            st = conf.students[id];
            ui->nameShow->setHtml(returnHtml(st, 255, 0, 255));
            cnt++;
            if (cnt>2*conf.num){
                ok=false;
                break;
            }
            if (st.count==0) break;
            Sleep(5);
        }
        if (ok) {
            ui->nameShow->setHtml(returnHtml(st, 255, 0, 255));
        }
        else {
            // 重置!
            for(int i = 0;i < conf.num;++i){
                conf.students[i].count=0;

            }
            ui->statusShow->setText(retHTML("已重置重复保护"));
            int id = QRandomGenerator64::global()->bounded(0, int(conf.num));
            st = conf.students[id];
        }
        ui->nameShow->setHtml(returnHtml(st, 255, 0, 255));
    }

    if (st.getId()>=0)conf.students[st.getId()-1].count++;
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
    if (randomedTimes > 1 && ui->statusShow->toHtml().indexOf("重置")==-1) {
        if (combo > 1)
            ui->statusShow->setText(retHTML("Total " + QString::number(randomedTimes) + "; Combo " + QString::number(combo)));
        else
            ui->statusShow->setText(retHTML("Total " + QString::number(randomedTimes)));
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
    return startHtml + "[" + Id + "]:<span style=\"color: rgb(0, 75, 255);\"><b>" +
           st.getName() + "</b></span>" + endHtml;
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
    return startHtml + "[" + Id + "] <span style=\"color: rgb(255, 104, 0); font-family: "
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
    int times = QRandomGenerator64::global()->bounded(15, 30);
    int sleepMS = QRandomGenerator64::global()->bounded(50, 70);
    qDebug() << "SleepTime: " << sleepMS;
    qDebug() << "Times: " << times;
    for (int i = 0; i < times; i++) {
        group gp = conf.groups[QRandomGenerator64::global()->bounded(
            0, int(conf.groupNum))];
        ui->nameShow->setHtml(returnHtmlByGroup(gp));
        qDebug() << "[" << gp.getId() << "] " << gp.getLeaderName();
        Sleep(sleepMS);
    }
    ui->random->setDisabled(false);
    ui->randomByGroup->setDisabled(false);
}

bool mainWindow::eventFilter(QObject* watched, QEvent* event)
{
    return true;
}

void mainWindow::on_stayOnTop_stateChanged(int arg1)
{
    this->hide();
    logw.hide();
    if (arg1 == Qt::Unchecked) {
        setWindowFlags(Qt::FramelessWindowHint);
        logw.setWindowFlags(Qt::WindowStaysOnTopHint);
        qDebug() << "Make Window no longer stay on top";
    } else {
        setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        logw.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        qDebug() << "Make Window stay on top";
    }
    this->show();
    if (ui->showLog->checkState() == Qt::Checked)
        logw.show();
}

void mainWindow::on_random_pressed()
{
    if (m_move)
        return;
    m_move = true;
    m_startPoint = QCursor::pos();
    m_windowPoint = this->frameGeometry().topLeft();
}

void mainWindow::on_randomByGroup_pressed()
{
    if (m_move)
        return;
    m_move = true;
    m_startPoint = QCursor::pos();
    m_windowPoint = this->frameGeometry().topLeft();
}

void mainWindow::on_exit_pressed()
{
    if (m_move)
        return;
    m_move = true;
    m_startPoint = QCursor::pos();
    m_windowPoint = this->frameGeometry().topLeft();
}

void mainWindow::on_showLog_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        logw.move(this->frameGeometry().topRight()+QPoint(7,0));
        logw.changeBackground();
        logw.setVisible(true);
        qDebug() << "Make Log Window Visible";
    } else {
        logw.setVisible(false);
        qDebug() << "Make Log Window Invisible";
    }
}

void mainWindow::LogMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    static QMutex mutex;
    mutex.lock();
    QString text;
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString message = QString("%1 %2").arg(current_date_time).arg(msg);
    MessageSender(message);
    mutex.unlock();
}

void mainWindow::MessageSender(QString msg) {
    window->logw.log(msg);
}
