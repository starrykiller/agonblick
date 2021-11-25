#ifndef SETTINGS_H
#define SETTINGS_H

#include "student.h"
#include <QVector>
#include <QFile>
#include <QTime>
#include <QWidget>
#include "group.h"

class settings
{
public:
    settings();
    bool read();
    QVector <student> students;
    QVector <group> groups;
    unsigned int num = 0;
    unsigned int groupNum = 0;
    QWidget* par;
};

#endif // SETTINGS_H
