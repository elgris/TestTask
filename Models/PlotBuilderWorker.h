#ifndef PLOTBUILDERWORKER_H
#define PLOTBUILDERWORKER_H
#include <QObject>

class PlotBuilder;
class Function;

/**
 * @brief Just a worker which performs calculations in a loop
 */
class PlotBuilderWorker : public QObject
{
    Q_OBJECT
public:
    PlotBuilderWorker(PlotBuilder * manager);
    /**
     * @brief Set start value for calculation
     * @param valueFrom
     */
    void setValueFrom(double valueFrom) { _valueFrom = valueFrom; }
    /**
     * @brief Set end value for calculation
     * @param valueTo
     */
    void setValueTo(double valueTo) { _valueTo = valueTo; }
    /**
     * @brief Set step of calculation
     * @param step
     */
    void setStep(double step) { _step = step; }

    /**
     * @brief Reset current calculation process
     */
    void reset() { _valueCurrent = _valueFrom; }

    /**
     * @brief Set function for calculations
     * @param function
     */
    void setFunction(Function *function) { _function = function; }

signals:
    void processed(double, double, double);
    void finished();

public slots:
    /**
     * @brief Perform calculations in loop
     */
    void process();

private:
    PlotBuilder * _manager;
    Function * _function;

    double _valueFrom;
    double _valueTo;
    double _valueCurrent;
    double _step;
    /**
     * @brief Calculate current builder's progress.
     * Returns value in range [0, 1]
     */
    double getProgress();
};

#endif // PLOTBUILDERWORKER_H
