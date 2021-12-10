#ifndef GROUP_H
#define GROUP_H
#include <QString>

class group {
public:
    group(QString, unsigned int);
    group();
    QString getLeaderName();
    int getId();
    void setLeaderName(QString name);
    void setId(int Id);
    bool operator==(group a)
    {
        if (a.getLeaderName() == this->getLeaderName() && a.getId() == this->getId())
            return true;
        return false;
    }

private:
    QString leaderName = "untitled";
    int Id = 0;
};

#endif // GROUP_H
