#ifndef FUNCTION_H
#define FUNCTION_H

#include <QString>
#include <QVector>

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
    const inline QVector<double> & getParameters() const { return this->_parameters; }

    /**
     * @brief Get string representation of the function
     * @return
     */
    const inline QString getFunctionString() const { return this->_functionString; }

    /**
     * @brief Set function's parameter value
     * @param parameterNumber
     * @param value
     */
    void setParameter(int parameterNumber, double value);

    /**
     * @brief Set function's parameters at once
     * @param parameters
     */
    void setParameters(const QVector<double> & parameters);

protected:
    QVector<double> _parameters;    // function's parameters (A, B, C, etc)
    QString _functionString;    // String representation of the function (for output)
};

#endif // FUNCTION_H
