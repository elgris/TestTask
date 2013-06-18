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
#include "Models/DataStorage.h"
#include <QSpacerItem>
#include <QMessageBox>
#include <QFileDialog>

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

    ui->actionSave->setShortcut(QKeySequence(tr("Ctrl+S")));
    ui->actionLoad->setShortcut(QKeySequence(tr("Ctrl+O")));

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
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveClicked()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadClicked()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

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
    Function * function = _plotControlWidget->getSelectedFunction();
    if(function == NULL) {
        QMessageBox::warning(this, "Warning!", "Function is not defined");
        return;
    }

    QVector<double> params = _plotControlWidget->getFunctionParameters();
    if(params.size() != function->getParameters().size()) {
        QMessageBox::warning(this, "Warning!", "Unsupported number of function prameters provided");
        return;
    }

    double step = _plotControlWidget->getValueStep();
    if(step == 0) {
        QMessageBox::warning(this, "Warning!", "Step value must be greater than zero");
        return;
    }

    double from = _plotControlWidget->getValueFrom();
    double to = _plotControlWidget->getValueTo();
    if(from > to) {
        QMessageBox::warning(this, "Warning!", "End value must be greater than start value");
        return;
    }

    function->setParameters(params);

    _plotBuilder->setRange(from, to);
    _plotBuilder->setStep(step);
    _plotBuilder->setFunction(function);

    _plotControlWidget->setEnabled(false);
    ui->startButton->setEnabled(true);

    emit startProcessing();
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

void  MainWindow::saveClicked()
{
    DataStorage storage;
    QString filename = QFileDialog::getSaveFileName(this,
                                 tr("Save File..."),
                                 QString(), tr("Plot files (*.plot);;All Files (*)"));

    storage.setFunctionIndex(_plotControlWidget->getSelectedFunctionIndex());
    storage.setFunctionParams(_plotControlWidget->getFunctionParameters());
    storage.setValueFrom(_plotControlWidget->getValueFrom());
    storage.setValueTo(_plotControlWidget->getValueTo());
    storage.setStep(_plotControlWidget->getValueStep());

    storage.setPoints(_points->getPoints());

    if(!storage.save(filename)) {
        QMessageBox::warning(this, "Warning!", "Could not save file with results!");
    }
}

void MainWindow::loadClicked()
{
    DataStorage storage;
    QString filename = QFileDialog::getOpenFileName(this,
                                 tr("Open File..."),
                                 QString(), tr("Plot files (*.plot);;All Files (*)"));
    if(!storage.load(filename)) {
        QMessageBox::warning(this, "Warning!", "Could not load file with results!");
        return;
    }

    if(!_plotControlWidget->setFunctionIndex(storage.getFunctionIndex())) {
        QMessageBox::warning(this, "Warning!", "Invalid function index was loaded!");
        return;
    }
    _plotControlWidget->setFunctionParameters(storage.getFunctionParams());

    if(storage.getValueFrom() > storage.getValueTo()) {
        QMessageBox::warning(this, "Warning!", "Invalid function values range was loaded! Begin value must be less or equal than end value");
        return;
    }
    _plotBuilder->setRange(storage.getValueFrom(), storage.getValueTo());
    _plotControlWidget->setValueFrom(storage.getValueFrom());
    _plotControlWidget->setValueTo(storage.getValueTo());

    if(storage.getStep() <= 0) {
        QMessageBox::warning(this, "Warning!", "Invalid calculation step was loaded. It must be greater than zero");
        return;
    }
    _plotBuilder->setStep(storage.getStep());
    _plotControlWidget->setValueStep(storage.getStep());

    _points->setPoints(storage.getPoints());
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
