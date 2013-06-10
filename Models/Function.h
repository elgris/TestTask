#ifndef FUNCTION_H
#define FUNCTION_H

#include <QString>
#include <QVector>

namespace Models {
    class Function;
}

/**
 * @brief Interface defines a Function - entity that is able to calculate
 * itself by some argument
 */
class Function {
public:
    Function(int parametersCount, QString functionString);

    /**
     * @brief Calculate value of the function
     * @param x - Argument of the function
     * @return
     */
    virtual double calculate(double x) = 0;

    /**
     * @brief Gets current function parameters
     * @return
     */
    const QList<double> & getParameters(); // @todo: why & is here? Explain

    /**
     * @brief Get string representation of the function
     * @return
     */
    QString getFunctionString();

    /**
     * @brief Set function's parameter value
     * @param parameterNumber
     * @param value
     */
    void setParameter(int parameterNumber, double value);

protected:
    QVector<double> _parameters;
    QString _functionString;
};

#endif // FUNCTION_H
