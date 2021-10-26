#ifndef SETTINGS_H
#define SETTINGS_H

#include "student.h"
#include <QVector>
#include <QFile>
#include <QTime>
#include <QWidget>

class settings
{
public:
    settings();
    bool read();
    QVector <student> rander;
    unsigned int num = 0;
    QWidget* par;
};

#endif // SETTINGS_H
