#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets/PlotControlWidget.h"
#include "Widgets/PlotWidget.h"
#include "Models/Logarithmic.h"
#include "Models/Inverse.h"
#include "Models/Quadratic.h"
#include "Models/Trigonometric.h"
#include "Models/PlotBuilder.h"
#include <QSpacerItem>


const QString MainWindow::LABEL_PAUSE = "Pause";
const QString MainWindow::LABEL_START = "Start";
const QString MainWindow::LABEL_CONTINUE = "Continue";
const QString MainWindow::LABEL_PROCESSING = "Process (%0%)";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _plotBuilder(new PlotBuilder)
{
    ui->setupUi(this);
    _plotControlWidget = new PlotControlWidget(this, loadFunctions());
    _plotWidget = new PlotWidget(this);

    ui->verticalLayout->insertWidget(0, _plotControlWidget);
    ui->verticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    ui->horizontalLayout->addWidget(_plotWidget);

    setupPlotBuilder();
}

MainWindow::~MainWindow()
{
    _plotBuilder->stop();
    delete _plotBuilder;
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
    _plotWidget->setMinX(from);
    _plotWidget->setMaxX(to);

    _plotBuilder->setValueFrom(from);
    _plotBuilder->setValueTo(to);
    _plotBuilder->setStep(step);
    _plotBuilder->setFunction(function);
    _plotWidget->resetPlot();

    _plotControlWidget->setEnabled(false);
    ui->startButton->setEnabled(true);
    emit startProcessing();
}

void MainWindow::setupPlotBuilder()
{
    connect(this, SIGNAL(startProcessing()), _plotBuilder, SLOT(start()));
    connect(ui->stopButton, SIGNAL(clicked()), _plotBuilder, SLOT(stop()));
    connect(this, SIGNAL(pauseProcessing()), _plotBuilder, SLOT(pause()));
    connect(this, SIGNAL(resumeProcessing()), _plotBuilder, SLOT(resume()));

    connect(_plotBuilder, SIGNAL(finished()), this, SLOT(processingFinished()));
    connect(_plotBuilder, SIGNAL(processed(double, double, double)), this, SLOT(valueProcessed(double, double, double)));
}

void MainWindow::pauseClicked()
{
    if(_plotBuilder->isProcessing()) {
        ui->pauseButton->setText(MainWindow::LABEL_CONTINUE);

        emit pauseProcessing();
    } else {
        ui->pauseButton->setText(MainWindow::LABEL_PAUSE);

        emit resumeProcessing();
    }
}

void MainWindow::valueProcessed(double x, double y, double progress)
{
    ui->startButton->setText(QString(MainWindow::LABEL_PROCESSING).arg((int)(progress * 100)));
    _plotWidget->addPoint(x, y);
}

void  MainWindow::processingFinished()
{
    _plotControlWidget->setEnabled(true);

    ui->startButton->setText(MainWindow::LABEL_START);
    ui->startButton->setEnabled(true);

    ui->pauseButton->setText(MainWindow::LABEL_PAUSE);
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
