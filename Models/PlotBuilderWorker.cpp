#include "PlotBuilderWorker.h"
#include "Function.h"
#include "PlotBuilder.h"


#include <QMutex>
#include <QWaitCondition>

PlotBuilderWorker::PlotBuilderWorker(PlotBuilder * manager):
    _manager(manager),
    _function(NULL)
{}

void PlotBuilderWorker::process()
{
    if(_function != NULL) {
        for(_valueCurrent;
            (_valueCurrent <= _valueTo) && _manager->isProcessing();
            _valueCurrent += _step) {
//            msleep(5);

            double y = _function->calculate(_valueCurrent);

            emit processed(_valueCurrent, y, getProgress());
        }

        if (_manager->isProcessing()) {
            emit finished();
        }
    }
}

double PlotBuilderWorker::getProgress()
{
    if(_valueTo <= _valueFrom) {
        return 1;
    }

    return (_valueCurrent  - _valueFrom) / (_valueTo - _valueFrom);
}

void PlotBuilderWorker::msleep(unsigned long msecs)
{
    QMutex mutex;
    mutex.lock();

    QWaitCondition waitCondition;
    waitCondition.wait(&mutex, msecs);

    mutex.unlock();
}
