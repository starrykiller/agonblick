#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class student

{
public:
    student(QString, unsigned int);
    QString getName();
    int getId();
    void setName(QString name);
    void setId(int Id);

private:
    QString name;
    int Id = 0;
};

#endif // STUDENT_H
