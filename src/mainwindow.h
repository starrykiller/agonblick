#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "settings.h"

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

private slots:
    void on_exit_clicked();

    void on_random_clicked();

private:
    Ui::mainWindow *ui;
    settings conf;
};
#endif // MAINWINDOW_H
