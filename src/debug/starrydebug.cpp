#include "starrydebug.h"
#include <QMutex>
#include <iostream>
#include <QDateTime>
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>

starryDebug::starryDebug()
{

}

//starryDebug单例
starryDebug* starryDebug::self = nullptr;
starryDebug* starryDebug::Instance()
{
    if(!self) {
        static QMutex muter;
        QMutexLocker clocker(&muter);

        if(!self) {
            self = new starryDebug();
        }
    }
    return self;
}
//安装消息器
void starryDebug::installMessageHandler()
{
    qInstallMessageHandler(outputMessage);
}
//卸载消息器
void starryDebug::uninstallMessageHandler()
{
    qInstallMessageHandler(0);
}
//建立文件路径
QString starryDebug::logPath()
{
    QString current_date_file_name = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QDir dir(QString("log/%1").arg(current_date_file_name));
    if(!dir.exists()) {
        dir.mkpath("./");
    }
    return dir.path() + "/" ;
}

QString starryDebug::logName()
{
    return "log.txt";
}

starryDebug::starryDebug(QObject *parent) : QObject(parent)
{
    static starryDebug::GC gc;
}

starryDebug::~starryDebug()
{
    std::cout << "~starryDebug" << std::endl;
}

//垃圾自动回收
starryDebug::GC::~GC()
{
    if (self != nullptr) {
        delete self;
        self = nullptr;
    }
}

