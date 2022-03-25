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
    QString msg = ui->logShow->toHtml() +
                  "<span style='font-family: Consolas, 微软雅黑; font-size: 14px; line-height: 14px;'>" +
                  l + "</span><br>\n";
    ui->logShow->setHtml(msg);
    QTextCursor cursor = ui->logShow->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logShow->setTextCursor(cursor);
}
