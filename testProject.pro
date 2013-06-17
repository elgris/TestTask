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
    Models/Function.cpp \
    Models/Quadratic.cpp \
    Models/Trigonometric.cpp \
    Models/Logarithmic.cpp \
    Models/Inverse.cpp \
    Widgets/PlotParametersWidget.cpp \
    Widgets/PlotControlWidget.cpp \
    Widgets/PlotWidget.cpp \
    Models/PlotBuilder.cpp \
    Models/PlotBuilderWorker.cpp \
    Models/PointsCollection.cpp \
    Models/DataStorage.cpp


HEADERS  += mainwindow.h \
    Models/Function.h \
    Models/Quadratic.h \
    Models/Trigonometric.h \
    Models/Logarithmic.h \
    Models/Inverse.h \
    Widgets/PlotParametersWidget.h \
    Widgets/PlotControlWidget.h \
    Widgets/PlotWidget.h \
    Models/PlotBuilder.h \
    Models/PlotBuilderWorker.h \
    Models/PointsCollection.h \
    Models/DataStorage.h

FORMS    += mainwindow.ui \
    Widgets/PlotParametersWidget.ui \
    Widgets/PlotControlWidget.ui \
    Widgets/PlotWidget.ui

OTHER_FILES += \
    README.txt \
    funcs.txt \
    .gitignore
