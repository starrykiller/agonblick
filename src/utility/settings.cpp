#include "settings.h"
#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QStringList>

settings::settings()
{
}

QStringList settings::returnListByLine(QString configFileName)
{
    try {
        QFile conf(QCoreApplication::applicationDirPath() + "\\config\\" + configFileName);
        conf.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!conf.exists()) {
            conf.close();
            ParseError = "未找到配置文件[" + configFileName + "]。";
            return QString("null").split("\n");
        }
        QString value = conf.readAll();
        conf.close();
        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
        if (!(parseJsonErr.error == QJsonParseError::NoError)) {
            qDebug() << parseJsonErr.errorString();
            ParseError = "[" + configFileName + "]JSON解析错误：" + parseJsonErr.errorString();
            return QString("null").split("\n");
        }
        QJsonObject jsonObject = document.object();
        QString type = jsonObject["type"].toString();
        QString version = jsonObject["version"].toString();
        if (version != "1.0.0") {
            ParseError = "[" + configFileName + "]JSON解析错误：不合规的版本号";
            return QString("null").split("\n");
        }
        qDebug() << "type=" + jsonObject["type"].toString();
        qDebug() << "version=" + jsonObject["version"].toString();
        if (type == "names") {
            QStringList list;
            QJsonValue arrayValue = jsonObject.value(QStringLiteral("names"));
            if (arrayValue.isArray()) {
                QJsonArray array = arrayValue.toArray();
                for (int i = 0; i < array.size(); i++) {
                    QJsonValue nameValue = array.at(i);
                    QString name = nameValue.toString();
                    list.append(name);
                }
            }
            return list;

        } else if (type == "groups") {
            QStringList list;
            QJsonValue arrayValue = jsonObject.value(QStringLiteral("groups"));
            if (arrayValue.isArray()) {
                QJsonArray array = arrayValue.toArray();
                for (int i = 0; i < array.size(); i++) {
                    QJsonObject groupArray = array.at(i).toObject();
                    QString groupName = groupArray["leaderName"].toString();
                    list.append(groupName);
                }
            }
            return list;
        } else if (type == "cps") {
            QStringList list;
            QJsonValue arrayValue = jsonObject.value(QStringLiteral("cps"));
            if (arrayValue.isArray()) {
                QJsonArray array = arrayValue.toArray();
                for (int i = 0; i < array.size(); i++) {
                    QJsonObject groupArray = array.at(i).toObject();
                    QString cp = groupArray["cpName"].toString() + "," + QString::number(groupArray["cp1"].toInt()) + "," + QString::number(groupArray["cp2"].toInt());
                    list.append(cp);
                }
            }
            return list;
        } else {
            ParseError = "[" + configFileName + "]JSON解析错误：不合规的类型[" + type + "]";
            return QString("null").split("\n");
        }

    } catch (std::exception& e) {
        ParseError = e.what();
        return QString("null").split("\n");
    }
    return QString("null").split("\n");
}

bool settings::read()
{
    // read names
    QStringList nameList = returnListByLine("names.json");
    if (nameList.at(0) == "null") {
        return false;
    }
    for (const auto& i : nameList) {
        this->num++;
        student st(i, this->num);
        students.append(st);
        qDebug() << st.getName() << " " << st.getId();
    }

    if (this->num == 1 && students[0].getName() == "")
        return false;
    qDebug() << "Name Total: " << this->num;

    // read groups
    QStringList groupList = returnListByLine("groups.json");
    if (groupList.at(0) == "null") {
        return false;
    }
    for (const auto& i : groupList) {
        this->groupNum++;
        group gp(i, this->groupNum);
        groups.append(gp);
        qDebug() << gp.getLeaderName() << " " << gp.getId();
    }
    if (this->groupNum == 1 && groups[0].getLeaderName() == "")
        return false;
    qDebug() << "Group Total: " << this->groupNum;

    // read CP

    QStringList cpList = returnListByLine("cps.json");
    if (groupList.at(0) == "null") {
        return false;
    }
    for (const auto& i : cpList) {
        this->cpNum++;
        QStringList cpSL = i.split(",");
        cp _cp = cp(0 - cpNum, cpSL.at(0), this->students[cpSL.at(1).toInt() - 1], this->students[cpSL.at(2).toInt() - 1]);
        cps.append(_cp);
        qDebug() << _cp.cpId << " " << _cp.cpName << " " << _cp.cp1.getName() << " " << _cp.cp2.getName();
    }
    if (this->groupNum == 1 && groups[0].getLeaderName() == "")
        return false;
    qDebug() << "cp Total: " << this->cpNum;
    return true;
}
