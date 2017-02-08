#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T19:17:39
#
#-------------------------------------------------
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tableModel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    connection.h

FORMS    += mainwindow.ui

RESOURCES += \
    tablemodel.qrc
