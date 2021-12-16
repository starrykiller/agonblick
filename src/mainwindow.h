#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "group.h"
#include "settings.h"
#include "student.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class mainWindow;
}
QT_END_NAMESPACE

class mainWindow : public QWidget {
    Q_OBJECT

public:
    mainWindow(QWidget* parent = nullptr);
    void Sleep(int msec);
    ~mainWindow();
    QString returnHtml(student st);
    QString returnHtml(student st, int r, int g, int b);
    QString returnHtmlByGroup(group gp);
    void paintEvent(QPaintEvent* event);

private slots:
    void on_exit_clicked();

    void on_random_clicked();

    void on_randomByGroup_clicked();
    void on_stayOnTop_stateChanged(int arg1);

    void on_random_pressed();

    void on_randomByGroup_pressed();

    void on_exit_pressed();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    const QString startHtml = "<span style='font-family: 如风似月行楷, \"comic sans MS\", 方正小标宋简体, 华文中宋, 微软雅黑; font-weight: 250; font-size: 40pt;'>";
    const QString endHtml = "</span>";
    Ui::mainWindow* ui;
    settings conf;
    student last;
    bool lastMQ = false;
    bool lastGC = false;
    bool eventFilter(QObject* watched, QEvent* event);
    bool nextMQCP = false;
    bool m_move = false;
    QPoint m_startPoint;
    QString returnHtmlByCP(cp CP);
    QPoint m_windowPoint;
    QVector<student> his;
    int cnt = 0;
};
#endif // MAINWINDOW_H
