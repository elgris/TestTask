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

    inline void setFunctionIndex(int value) { _functionIndex = value; }
    inline void setValueFrom(double value) { _valueFrom = value; }
    inline void setValueTo(double value) { _valueTo = value; }
    inline void setStep(double value) { _step = value; }
    inline void setFunctionParams(const QVector<double> & value) { _functionParams = value; }
    inline void setPoints(const QVector<QPointF> & value) { _points = value; }

    inline int getFunctionIndex() const { return _functionIndex;}
    inline double getValueFrom() const { return _valueFrom; }
    inline double getValueTo() const { return _valueTo; }
    inline double getStep() const { return _step; }
    inline QVector<double> & getFunctionParams() { return _functionParams; }
    inline QVector<QPointF> & getPoints() { return _points; }

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
