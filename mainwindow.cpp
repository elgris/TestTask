#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets/PlotControlWidget.h"
#include "Widgets/PlotWidget.h"
#include "Models/Logarithmic.h"
#include "Models/Inverse.h"
#include "Models/Quadratic.h"
#include "Models/Trigonometric.h"
#include "Models/PlotBuilder.h"
#include "Models/PointsCollection.h"
#include <QSpacerItem>
#include <QMessageBox>
#include <stdexcept>

const QString MainWindow::LABEL_PAUSE = "Pause";
const QString MainWindow::LABEL_START = "Start";
const QString MainWindow::LABEL_CONTINUE = "Continue";
const QString MainWindow::LABEL_PROCESSING = "Process (%0%)";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _points(new PointsCollection),
    _plotBuilder(new PlotBuilder)
{
    ui->setupUi(this);
    _plotControlWidget = new PlotControlWidget(this, loadFunctions());
    _plotWidget = new PlotWidget(this, _points);

    ui->verticalLayout->insertWidget(0, _plotControlWidget);
    ui->verticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    ui->horizontalLayout->addWidget(_plotWidget);

    setupConnections();
}

MainWindow::~MainWindow()
{
    _plotBuilder->stop();
    delete _plotBuilder;
    delete _points;
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(this, SIGNAL(startProcessing()), _plotBuilder, SLOT(start()));
    connect(ui->stopButton, SIGNAL(clicked()), _plotBuilder, SLOT(stop()));
    connect(this, SIGNAL(pauseProcessing()), _plotBuilder, SLOT(pause()));
    connect(this, SIGNAL(resumeProcessing()), _plotBuilder, SLOT(resume()));

    connect(_plotBuilder, SIGNAL(finished()), this, SLOT(processingFinished()));
    connect(_plotBuilder, SIGNAL(processed(double, double, double)), this, SLOT(valueProcessed(double, double, double)));

    connect(_plotBuilder, SIGNAL(processed(double, double, double)), _points, SLOT(addPoint(double, double)));
    connect(_plotBuilder, SIGNAL(started()), _points, SLOT(clear()));
}

void MainWindow::startClicked()
{
    try {
        Function * function = _plotControlWidget->getSelectedFunction();
        function->setParameters(_plotControlWidget->getFunctionParameters());

        double from = _plotControlWidget->getValueFrom();
        double to = _plotControlWidget->getValueTo();
        double step = _plotControlWidget->getValueStep();

        _plotBuilder->setRange(from, to);
        _plotBuilder->setStep(step);
        _plotBuilder->setFunction(function);

        _plotControlWidget->setEnabled(false);
        ui->startButton->setEnabled(true);

        emit startProcessing();
    } catch (std::runtime_error &e) {
        QMessageBox::warning(this, "Warning!", e.what());
    }
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
}

void  MainWindow::processingFinished()
{
    _plotControlWidget->setEnabled(true);

    ui->startButton->setText(MainWindow::LABEL_START);
    ui->startButton->setEnabled(true);

    ui->pauseButton->setText(MainWindow::LABEL_PAUSE);
}

//void  MainWindow::saveResults()
//{

//}

//void  MainWindow::loadResults()
//{
//    int functionIndex;
//    double from;
//    double to;
//    double step;
//    double current;
//    QVector<double> functionParameters;
//    QVector<QPointF> points;

//    // read function index
//    // read array of parameters
//    // read points

//    try {
//        _plotControlWidget->setFunctionIndex(functionIndex);
//        _plotControlWidget->setFunctionParameters(functionParameters);
//        _plotBuilder->setFunction(_plotControlWidget->getSelectedFunction());

//        double progress = _plotBuilder->getProgress();
//        ui->startButton->setText(QString("%0 %1")
//                                 .arg(MainWindow::LABEL_START,
//                                     QString(MainWindow::LABEL_PROCESSING).arg((int)(progress * 100)));
//    } catch(std::exception e) {
//        QMessageBox::warning(this, "Could not load calculation data!", e.what());
//    }
//}

QVector<Function *> * MainWindow::loadFunctions()
{
    QVector<Function *> * functions = new QVector<Function *>();
    functions->append(new Quadratic());
    functions->append(new Trigonometric());
    functions->append(new Logarithmic());
    functions->append(new Inverse());

    return functions;
}
