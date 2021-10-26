#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "settings.h"
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    void Sleep(int msec);
    ~mainWindow();
    QString returnHtml(student st);

private slots:
    void on_exit_clicked();

    void on_random_clicked();

private:
    const QString startHtml = "<span style='font-family: consolas, 方正小标宋简体, 华文中宋, 微软雅黑; font-weight: 300; font-size: 40pt;'>";
    const QString endHtml = "</span>";
    Ui::mainWindow *ui;
    settings conf;
    student last;
};
#endif // MAINWINDOW_H
