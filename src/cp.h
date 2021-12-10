#ifndef CP_H
#define CP_H
#include "student.h"

class cp {
public:
    cp();
    cp(int id, QString, student _1, student _2);
    int cpId = -1;
    QString cpName;
    student cp1;
    student cp2;
};

#endif // CP_H
