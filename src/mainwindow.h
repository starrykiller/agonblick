#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "settings.h"
#include "student.h"
#include "group.h"

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
    QString returnHtml(student st, int r, int g, int b);
    QString returnHtmlByGroup(group gp);

private slots:
    void on_exit_clicked();

    void on_random_clicked();

    void on_randomByGroup_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    const QString startHtml = "<span style='font-family: consolas, 方正小标宋简体, 华文中宋, 微软雅黑; font-weight: 300; font-size: 40pt;'>";
    const QString endHtml = "</span>";
    Ui::mainWindow *ui;
    settings conf;
    student last;
    bool lastMQ = false;
    bool eventFilter(QObject *watched, QEvent *event);
    bool nextMQCP = false;
    bool m_move = false;
    QPoint m_startPoint;
    QPoint m_windowPoint;
};
#endif // MAINWINDOW_H
