#include "Logarithmic.h"
#include "math.h"

Logarithmic::Logarithmic()
    :Function(2, QString("f(x) = A*log( B*x )"))
{
}

double Logarithmic::calculate(double x) {
    double arg = this->_parameters[1] * x;

    return arg <= 0
            ? 0
            : this->_parameters[0] * log(arg);
}
