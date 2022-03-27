#include "logwindow.h"
#include "ui_logwindow.h"
#include "starrywindow.h"

logWindow::logWindow(QWidget *parent) :
    starryWindow(parent),
    ui(new Ui::logWindow)
{
    ui->setupUi(this);
}

logWindow::~logWindow()
{
    delete ui;
}

void logWindow::log(QString l) {
    QString msg;
    if (l.toLower().indexOf("fatal") != -1)
        msg = ui->logShow->toHtml() +
                  "<span style='font-family: Consolas, 微软雅黑; font-size: 18px; line-height: 18px; color: red;'><b>" +
                  l + "</b></span>";
    else if (l.toLower().indexOf("error") != -1)
        msg = ui->logShow->toHtml() +
              "<span style='font-family: Consolas, 微软雅黑; font-size: 18px; line-height: 18px; color: red;'>" +
              l + "</span>";
    else if (l.toLower().indexOf("warning") != -1)
        msg = ui->logShow->toHtml() +
              "<span style='font-family: Consolas, 微软雅黑; font-size: 14px; line-height: 14px; color: #F70;'>" +
              l + "</span>";
    else
        msg = ui->logShow->toHtml() +
                      "<span style='font-family: Consolas, 微软雅黑; font-size: 14px; line-height: 14px;'>" +
                      l + "</span>";
    ui->logShow->setHtml(msg);
    QTextCursor cursor = ui->logShow->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logShow->setTextCursor(cursor);
}
