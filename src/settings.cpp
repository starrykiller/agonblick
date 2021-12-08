#include "settings.h"
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>

settings::settings()
{

}

QStringList settings::returnListByLine(QString configFileName) {
    QFile conf(QCoreApplication::applicationDirPath() + "\\config\\" + configFileName);
    conf.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!conf.exists()) {
        conf.close();
        return QString("null").split("\n");
    }
    QStringList l = QString(conf.readAll()).split("\n");
    conf.close();
    return l;
}

bool settings::read() {
    // read names
    QStringList nameList = returnListByLine("names.ini");
    if (nameList.at(0) == "null") {
        return false;
    }
    for (const auto& i : nameList) {
        this->num++;
        student st(i, this->num);
        students.append(st);
        qDebug() << st.getName() << " " << st.getId();
    }

    if (this->num == 1 && students[0].getName() == "") return false;
    qDebug() << "Name Total: " << this->num;

    // read groups
    QStringList groupList = returnListByLine("groups.ini");
    if (groupList.at(0) == "null") {
        return false;
    }
    for (const auto& i : groupList) {
        this->groupNum++;
        group gp(i, this->groupNum);
        groups.append(gp);
        qDebug() << gp.getLeaderName() << " " << gp.getId();
    }
    if (this->groupNum == 1 && groups[0].getLeaderName() == "") return false;
    qDebug() << "Group Total: " << this->num;
    return true;
}
