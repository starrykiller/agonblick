#include "student.h"

student::student(QString name, unsigned int Id)
{
    this->name=name, this->Id=Id;
}

student::student() {

}

QString student::getName() {
    return this->name;
}
int student::getId() {
    return this->Id;
}
void student::setName(QString name) {
    this->name=name;
}
void student::setId(int Id) {
    this->Id=Id;
}
