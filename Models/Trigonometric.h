#ifndef TRIGONOMETRIC_H
#define TRIGONOMETRIC_H
#include "Function.h"
namespace Models {
    class Trigonometric;
}
/**
 * @brief The Trigonometric function
 * f(x) = A * sin(x) + B * cos( C*x )
 */
class Trigonometric : public Function
{
public:
    Trigonometric();
    double calculate(double x);
};

#endif // TRIGONOMETRIC_H
