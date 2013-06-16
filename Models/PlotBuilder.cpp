#include "PlotBuilder.h"
#include "Function.h"
#include "../Widgets/PlotWidget.h"
#include <QThread>

PlotBuilder::PlotBuilder(QObject *parent) :
    QObject(parent),
    _isProcessing(false),
    _worker(new PlotBuilderWorker(this))
{
    QThread* thread = new QThread;
    _worker->moveToThread(thread);

    connect(this, SIGNAL(started()), _worker, SLOT(process()));
    connect(this, SIGNAL(resumed()), _worker, SLOT(process()));
    connect(_worker, SIGNAL(processed(double, double, double)), this, SIGNAL(processed(double, double, double)));

    thread->start();
}

PlotBuilder::~PlotBuilder()
{
    delete _worker;
}

void PlotBuilder::start()
{
    if(!isProcessing()) {
        _worker->reset();
        _isProcessing = true;

        emit started();
    }
}

void PlotBuilder::stop()
{
    _isProcessing = false;

    emit finished();
}

void PlotBuilder::pause()
{
    _isProcessing = false;

    emit paused();
}

void PlotBuilder::resume()
{
    _isProcessing = true;

    emit resumed();
}
