#ifndef SETTINGS_H
#define SETTINGS_H

#include "student.h"
#include <QVector>
#include <QFile>
#include <QTime>
#include <QWidget>
#include "group.h"
#include "cp.h"

class settings
{
public:
    settings();
    bool read();
    QVector <student> students;
    QVector <group> groups;
    QVector <cp> cps;
    unsigned int num = 0;
    unsigned int groupNum = 0;
    unsigned int cpNum = 0;
    QWidget* par;
    QStringList returnListByLine(QString configFileName);
    QString ParseError = "";
};

#endif // SETTINGS_H
