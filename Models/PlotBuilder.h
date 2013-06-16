#ifndef PLOTBUILDER_H
#define PLOTBUILDER_H

#include <QObject>
#include "PlotBuilderWorker.h"

class Function;
class PlotWidget;

/**
 * @brief The class is responsible for building plots
 * Supposed to be used in separate thread
 */
class PlotBuilder : public QObject
{
    Q_OBJECT
public:
    explicit PlotBuilder(QObject *parent = 0);
    ~PlotBuilder();
    
    void setValueFrom(double valueFrom) { _worker->setValueFrom(valueFrom); }
    void setValueTo(double valueTo) { _worker->setValueTo((valueTo)); }
    void setStep(double step) { _worker->setStep(step); }

    void setFunction(Function *function) { _worker->setFunction(function); }
    bool isProcessing() { return _isProcessing; }

signals:
    void started();
    void finished();
    void paused();
    void resumed();
    void processed(double, double, double);

public slots:
    void start();
    void pause();
    void resume();
    void stop();

private:
    bool _isProcessing;
    PlotBuilderWorker * _worker;
};

#endif // PLOTBUILDER_H
