#ifndef LOGARITHMIC_H
#define LOGARITHMIC_H
#include "Function.h"

namespace Models {
    class Logarithmic;
}
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
