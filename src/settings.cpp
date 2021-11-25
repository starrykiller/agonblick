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

bool settings::read() {
    // read names
    QFile f(QCoreApplication::applicationDirPath() + "\\names.ini");
    if (!f.exists()) {
        return false;
    }
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = f.readAll();
    QString s(t);
    f.close();
    QStringList list = s.split("\n");
    QStringListIterator iter(list);
    while (iter.hasNext()) {
        this->num++;
        student st(iter.next(), this->num);
        students.append(st);
        qDebug() << st.getName() << " " << st.getId();
    }
    if (this->num == 1 && students[0].getName() == "") return false;
    qDebug() << "Name Total: " << this->num;

    QFile f1(QCoreApplication::applicationDirPath() + "\\groups.ini");
    if (!f1.exists()) {
        return false;
    }
    f1.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t1 = f1.readAll();
    QString s1(t1);
    f1.close();
    QStringList list1 = s1.split("\n");
    QStringListIterator iter1(list1);
    while (iter1.hasNext()) {
        this->groupNum++;
        group gp(iter1.next(), this->groupNum);
        groups.append(gp);
        qDebug() << gp.getLeaderName() << " " << gp.getId();
    }
    if (this->groupNum == 1 && groups[0].getLeaderName() == "") return false;
    qDebug() << "Total: " << this->num;
    return true;
}
