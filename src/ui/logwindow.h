#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include "starrywindow.h"

namespace Ui {
class logWindow;
}

class logWindow : public starryWindow
{
    Q_OBJECT

public:
    explicit logWindow(QWidget *parent = nullptr);
    ~logWindow();
    void log(QString);

//public slots:

private:
    Ui::logWindow *ui;
};

#endif // LOGWINDOW_H
