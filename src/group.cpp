#include "group.h"

group::group(QString name, unsigned int Id)
{
    this->leaderName = name, this->Id = Id;
}

group::group()
{
}

QString group::getLeaderName()
{
    return this->leaderName;
}
int group::getId()
{
    return this->Id;
}
void group::setLeaderName(QString name)
{
    this->leaderName = name;
}
void group::setId(int Id)
{
    this->Id = Id;
}
