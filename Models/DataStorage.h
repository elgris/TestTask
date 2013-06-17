#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <QVector>
#include <QPointF>
/**
 * @brief Class manages storing/loading application data
 * During loading checks all needed constraints. If at least one constraint failed,
 * all loading process will be failed as well
 */
class DataStorage
{
public:
    DataStorage();

    void setFunctionIndex(int value) { _functionIndex = value; }
    void setValueFrom(int value) { _valueFrom = value; }
    void setValueTo(int value) { _valueTo = value; }
    void setStep(int value) { _step = value; }
    void setFunctionParams(const QVector<double> & value) { _functionParams = value; }
    void setPoints(const QVector<QPointF> & value) { _points = value; }

    int getFunctionIndex() { return _functionIndex;}
    int getValueFrom() { return _valueFrom; }
    int getValueTo() { return _valueTo; }
    int getStep() { return _step; }
    QVector<double> & getFunctionParams() { return _functionParams; }
    QVector<QPointF> & getPoints() { return _points; }

    bool save(QString filename) const;
    bool load(QString filename);

private:
    int _functionIndex;
    double _valueFrom;
    double _valueTo;
    double _step;
    QVector<double> _functionParams;
    QVector<QPointF> _points;
};

#endif // DATASTORAGE_H
