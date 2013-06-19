#ifndef QUADRATIC_H
#define QUADRATIC_H
#include "Function.h"

/**
 * @brief The Quadratic function
 * f(x) = A*(x*x) + B*x + C
 */
class Quadratic : public Function
{
public:
    Quadratic();
    double calculate(double x);
};

#endif // QUADRATIC_H
