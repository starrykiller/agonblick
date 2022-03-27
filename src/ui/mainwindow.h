#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "starrywindow.h"
#include "logwindow.h"

#include "../utility/group.h"
#include "../utility/settings.h"
#include "../utility/student.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class mainWindow;
}
QT_END_NAMESPACE

class mainWindow : public starryWindow {
    Q_OBJECT

public:
    mainWindow(QWidget* parent = nullptr);
    void Sleep(int msec);
    ~mainWindow();
    QString returnHtml(student st);
    QString returnHtml(student st, int r, int g, int b);
    QString returnHtmlByGroup(group gp);
    logWindow logw;
    static void LogMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static void MessageSender(QString);


private slots:
    void on_exit_clicked();
    void on_random_clicked();
    void on_randomByGroup_clicked();
    void on_stayOnTop_stateChanged(int arg1);
    void on_random_pressed();
    void on_randomByGroup_pressed();
    void on_exit_pressed();

    void on_showLog_stateChanged(int arg1);

private:
    starryWindow win;
    const QString startHtml = "<span style='font-family: 如风似月行楷, \"comic sans MS\", 方正小标宋简体, 华文中宋, 微软雅黑; font-weight: 250; font-size: 40pt;'>";
    const QString endHtml = "</span>";
    Ui::mainWindow* ui;
    settings conf;
    student last;
    bool eventFilter(QObject* watched, QEvent* event);
    QString returnHtmlByCP(cp CP);
    QVector<student> his;
    static mainWindow* window;
    int cnt = 0;
};
#endif // MAINWINDOW_H
