#-------------------------------------------------
#
# Project created by QtCreator 2013-06-08T22:46:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plotcontrolwidget.cpp \
    plotparameterswidget.cpp

HEADERS  += mainwindow.h \
    plotcontrolwidget.h \
    plotparameterswidget.h

FORMS    += mainwindow.ui \
    plotcontrolwidget.ui \
    plotparameterswidget.ui

OTHER_FILES += \
    README.txt \
    funcs.txt \
    .gitignore
