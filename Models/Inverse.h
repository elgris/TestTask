#ifndef INVERSE_H
#define INVERSE_H
#include "Function.h"

/**
 * @brief The Inverse function
 * f(x) = A / ( sin(x*x) * B )
 */
class Inverse : public Function
{
public:
    Inverse();
    double calculate(double x);
};

#endif // INVERSE_H
