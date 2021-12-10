#include "cp.h"

cp::cp()
{
}

cp::cp(int id, QString name, student _1, student _2)
{
    this->cpName = name;
    this->cpId = id;
    this->cp1 = _1;
    this->cp2 = _2;
}
