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
    
    /**
     * @brief Set start ans end value for calculations
     * @param valueFrom
     * @param valueTo
     * @throws std::runtime_error
     */
    void setRange(double valueFrom, double valueTo);

    /**
     * @brief Set step of calculation
     * @param step
     * @throws std::runtime_error
     */
    void setStep(double step);

    /**
     * @brief Set function for calculations
     * @param function
     * @throws std::runtime_error
     */
    void setFunction(Function *function);
    /**
     * @brief Determine whether calculation process still in progress
     * @return
     */
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
