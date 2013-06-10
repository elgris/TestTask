#include "Trigonometric.h"
#include <tgmath.h>
Trigonometric::Trigonometric()
    :Function(3, QString("f(x) = A * sin(x) + B * cos( C*x )"))
{
}

double Trigonometric::calculate(double x) {
    return this->_parameters[0] * sin(x)
            + this->_parameters[1] * (cos(x) * this->_parameters[2]);
}
