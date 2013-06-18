#include "DataStorage.h"
#include <QFile>
#include <QTextStream>

DataStorage::DataStorage()
{
}

bool DataStorage::save(QString filename) const
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);

    out << _functionIndex << endl;
    out << _valueFrom << " " << _valueTo << " " << _step << endl;

    out << _functionParams.size() << endl;
    for (QVector<double>::ConstIterator it = _functionParams.begin(); it != _functionParams.end(); it++) {
        out << *it << endl;
    }

    out << _points.size() << endl;
    for (QVector<QPointF>::ConstIterator it = _points.begin(); it != _points.end(); it++) {
        out << it->x() << " " << it->y() << endl;
    }

    file.close();

    return true;
}
bool DataStorage::load(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);

    in >> _functionIndex;
    in >> _valueFrom >> _valueTo >> _step;

    int functionParamsNumber;
    in >> functionParamsNumber;
    _functionParams.clear();
    for(int i = 0; i < functionParamsNumber; ++i) {
        double param;
        in >> param;
        _functionParams.append(param);
    }

    int pointsNumber;
    in >> pointsNumber;
    _points.clear();
    for(int i = 0; i < pointsNumber; ++i) {
        double x, y;
        in >> x >> y;
        _points.append(QPointF(x, y));
    }

    file.close();
    // last check: if we read expectable number of points, that means reading was performed well
    // otherwise - something wrong could happen
    // it's very simple validation mechanism
    return _points.size() == pointsNumber;
}
