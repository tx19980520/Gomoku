#-------------------------------------------------
#
# Project created by QtCreator 2017-07-21T21:18:53
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gomoku
TEMPLATE = app


SOURCES += main.cpp \
    maindialog.cpp \
    logdialog.cpp \
    editdialog.cpp \
    createdialog.cpp \
    chessdialog.cpp \
    rankdialog.cpp

HEADERS  += \
    maindialog.h \
    logdialog.h \
    editdialog.h \
    createdialog.h \
    chessdialog.h \
    rankdialog.h

FORMS    += \
    maindialog.ui \
    logDialog.ui \
    editdialog.ui \
    createdialog.ui \
    chessdialog.ui \
    rankdialog.ui
