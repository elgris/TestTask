#include "Logarithmic.h"
#include "math.h"

Logarithmic::Logarithmic()
    :Function(2, QString("f(x) = A*log( B*x )"))
{
}

double Logarithmic::calculate(double x) {
    return this->_parameters[0] * log(this->_parameters[1] * x);
}
