#include "PlotBuilder.h"
#include "Function.h"
#include "../Widgets/PlotWidget.h"
#include <QMutex>
#include <QWaitCondition>
PlotBuilder::PlotBuilder(QObject *parent) :
    QObject(parent),
    _function(NULL),
    _valueFrom(0),
    _valueTo(0),
    _step(0),
    _isProcessing(false)
{}
void PlotBuilder::msleep(unsigned long msecs)
{
    QMutex mutex;
    mutex.lock();

    QWaitCondition waitCondition;
    waitCondition.wait(&mutex, msecs);

    mutex.unlock();
}
void PlotBuilder::start()
{
    _valueCurrent = _valueFrom;
    process();
}

void PlotBuilder::stop()
{
    _isProcessing = false;
    _valueCurrent = _valueTo + _step;

    emit finished();
}

void PlotBuilder::pause()
{
    _isProcessing = false;
}

void PlotBuilder::resume()
{
    process();
}

void PlotBuilder::process()
{
    _isProcessing = true;

    for(_valueCurrent;
        (_valueCurrent <= _valueTo) && _isProcessing;
        _valueCurrent += _step) {
        msleep(10);

        double y = _function->calculate(_valueCurrent);

        emit processed(_valueCurrent, y, getProgress());
    }

    if (_isProcessing) {
        stop();
    }
}

double PlotBuilder::getProgress()
{
    if(_valueTo <= _valueFrom) {
        return 1;
    }

    return _valueCurrent / (_valueFrom - _valueTo);
}
