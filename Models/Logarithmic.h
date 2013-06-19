#ifndef LOGARITHMIC_H
#define LOGARITHMIC_H
#include "Function.h"

/**
 * @brief The Logarithmic function
 * f(x) = A*log( B*x )
 */
class Logarithmic : public Function
{
public:
    Logarithmic();
    double calculate(double x);
};
#endif // LOGARITHMIC_H
