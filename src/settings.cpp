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
        rander.append(st);
        qDebug() << st.getName() << " " << st.getId();
    }
    if (this->num == 1 && rander[0].getName() == "") return false;
    qDebug() << "Total: " << this->num;
    return true;
}
