#include "Function.h"
#include <stdexcept>

Function::Function(int parametersCount, QString functionString)
{
    _parameters.fill(0, parametersCount);
    _functionString = functionString;
}

void Function::setParameter(int parameterNumber, double value)
{
    if(parameterNumber > _parameters.size() || parameterNumber < 0) {
        throw new std::out_of_range("Invalid parameter number");
    }

    _parameters[parameterNumber] = value;
}

void Function::setParameters(const QVector<double> & parameters)
{
    for(int i = 0; i < _parameters.size(); ++i) {
        setParameter(i, parameters[i]);
    }
}
