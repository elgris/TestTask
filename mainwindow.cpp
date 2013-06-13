#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets/PlotControlWidget.h"
#include "Widgets/PlotWidget.h"
#include "Models/Logarithmic.h"
#include "Models/Inverse.h"
#include "Models/Quadratic.h"
#include "Models/Trigonometric.h"
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _plotControlWidget = new PlotControlWidget(this, loadFunctions());
    _plotWidget = new PlotWidget(this);

    ui->verticalLayout->insertWidget(0, _plotControlWidget);
    ui->verticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    ui->horizontalLayout->addWidget(_plotWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startClicked()
{
    Function * function = _plotControlWidget->getSelectedFunction();
    if(function == NULL) {
        return;
    }

    QVector<double> params = _plotControlWidget->getFunctionParameters();
    if(params.size() != function->getParameters().size()) {
        return;
    }

    double step = _plotControlWidget->getValueStep();
    if(step == 0) {
        return;
    }

    function->setParameters(params);
    double from = _plotControlWidget->getValueFrom();
    double to = _plotControlWidget->getValueTo();


    for(double x = from; x < to; x += step) {
        double y = function->calculate(x);

        _plotWidget->addPoint(x, y);
    }
}

void MainWindow::stopClicked()
{

}

void MainWindow::pauseClicked()
{

}

QVector<Function *> * MainWindow::loadFunctions()
{
    QVector<Function *> * functions = new QVector<Function *>();
    functions->append(new Quadratic());
    functions->append(new Trigonometric());
    functions->append(new Logarithmic());
    functions->append(new Inverse());

    return functions;
}
