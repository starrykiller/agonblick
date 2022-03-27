QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/utility/cp.cpp \
    src/utility/group.cpp \
    src/ui/logwindow.cpp \
    src/ui/starrywindow.cpp \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/utility/settings.cpp \
    src/utility/student.cpp

HEADERS += \
    src/utility/cp.h \
    src/utility/group.h \
    src/ui/logwindow.h \
    src/ui/starrywindow.h \
    src/ui/mainwindow.h \
    src/utility/settings.h \
    src/utility/student.h

FORMS += \
    src/ui/logwindow.ui \
    src/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources\\background.qrc

RC_FILE = icon.rc

QMAKE_TARGET_PRODUCT = Agonblick
QMAKE_TARGET_COMPANY = "starry studio"
QMAKE_TARGET_DESCRIPTION = "A program to choose a student randomly."
QMAKE_TARGET_COPYRIGHT = "starry killer"

DISTFILES += \
    .code-format
