#include "Function.h"
#include <stdexcept>

Function::Function(int parametersCount, QString functionString) {
    this->_parameters.fill(0, parametersCount);
    this->_functionString = functionString;
}

void Function::setParameter(int parameterNumber, double value) {
    if(parameterNumber > this->_parameters.size() || parameterNumber < 0) {
        throw new std::out_of_range("Invalid parameter number");
    }

    this->_parameters[parameterNumber] = value;
}

QString Function::getFunctionString() {
    return this->_functionString;
}
