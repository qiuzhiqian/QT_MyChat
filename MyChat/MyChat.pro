#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T08:44:23
#
#-------------------------------------------------

QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyChat
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    register.cpp \
    form.cpp

HEADERS  += \
    login.h \
    register.h \
    form.h

FORMS    += \
    login.ui \
    register.ui \
    form.ui

RESOURCES += \
    chat.qrc
