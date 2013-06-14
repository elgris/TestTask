#ifndef PLOTBUILDER_H
#define PLOTBUILDER_H

#include <QObject>
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
    
    void setValueFrom(double valueFrom) { _valueFrom = valueFrom; }
    void setValueTo(double valueTo) { _valueTo = valueTo; }
    void setStep(double step) { _step = step; }

    void setFunction(Function *function) { _function = function; }

signals:
    void finished();
    void paused();
    void processed(double, double, double);

public slots:
    void start();
    void pause();
    void resume();
    void stop();

    
private:
    double _valueFrom;
    double _valueTo;
    double _valueCurrent;
    double _step;

    bool _isProcessing;

    Function *_function;

    /**
     * @brief Perform calculations
     */
    void process();

    /**
     * @brief Calculate current builder's progress.
     * Returns value in range [0, 1]
     */
    double getProgress();

    void msleep(unsigned long msecs);
};

#endif // PLOTBUILDER_H
