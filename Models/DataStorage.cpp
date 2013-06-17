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

    for (QVector<double>::ConstIterator it = _functionParams.begin(); it != _functionParams.end(); it++) {
        out << *it << " ";
    }
    out << endl;

    for (QVector<QPointF>::ConstIterator it = _points.begin(); it != _points.end(); it++) {
        out << it->x() << " " << it->y() << endl;
    }

    file.close();

    return true;
}
bool DataStorage::load(QString filename)
{
    return false;
}
