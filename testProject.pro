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
    Widgets/plotparameterswidget.cpp \
    Widgets/plotcontrolwidget.cpp \
    Models/Function.cpp \
    Models/Quadratic.cpp \
    Models/Trigonometric.cpp \
    Models/Logarithmic.cpp \
    Models/Inverse.cpp

HEADERS  += mainwindow.h \
    Widgets/plotparameterswidget.h \
    Widgets/plotcontrolwidget.h \
    Models/Function.h \
    Models/Quadratic.h \
    Models/Trigonometric.h \
    Models/Logarithmic.h \
    Models/Inverse.h

FORMS    += mainwindow.ui \
    Widgets/plotparameterswidget.ui \
    Widgets/plotcontrolwidget.ui

OTHER_FILES += \
    README.txt \
    funcs.txt \
    .gitignore
