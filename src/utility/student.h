#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class student

{
public:
    student(QString, unsigned int);
    student();
    QString getName();
    int getId();
    void setName(QString name);
    void setId(int Id);
    int count=0;
    bool operator==(student a)
    {
        if (a.getName() == this->getName() && a.getId() == this->getId())
            return true;
        return false;
    }

private:
    QString name = "untitled";
    int Id = 0;
};

#endif // STUDENT_H
