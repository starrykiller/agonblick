#ifndef SETTINGS_H
#define SETTINGS_H

#include "cp.h"
#include "group.h"
#include "student.h"
#include <QFile>
#include <QTime>
#include <QVector>
#include <QWidget>

class settings {
public:
    settings();
    bool read();
    QVector<student> students;
    QVector<group> groups;
    QVector<cp> cps;
    unsigned int num = 0;
    unsigned int groupNum = 0;
    unsigned int cpNum = 0;
    QWidget* par;
    QStringList returnListByLine(QString configFileName);
    QString ParseError = "";
};

#endif // SETTINGS_H
