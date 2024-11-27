#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include <type_traits>

/**
 * @file basic_operations.h
 * @brief Módulo Basic Operations: Proporciona operaciones matemáticas básicas con validaciones avanzadas.
 * 
 * Este módulo soporta múltiples tipos de datos (int, float, double, etc.) mediante el uso de plantillas.
 */

class BasicOperations {
public:
    /**
     * @brief Realiza la suma de dos valores con validación de desbordamiento.
     * @tparam T Tipo de dato (int, float, double, etc.).
     * @param a Primer operando.
     * @param b Segundo operando.
     * @return Resultado de la suma.
     * @throws std::overflow_error en caso de desbordamiento (para tipos enteros).
     */
    template <typename T>
    static T add(T a, T b);

    /**
     * @brief Realiza la resta de dos valores con validación de subdesbordamiento.
     * @tparam T Tipo de dato (int, float, double, etc.).
     * @param a Primer operando.
     * @param b Segundo operando.
     * @return Resultado de la resta.
     * @throws std::underflow_error en caso de subdesbordamiento (para tipos enteros).
     */
    template <typename T>
    static T subtract(T a, T b);

    /**
     * @brief Realiza la multiplicación de dos valores con validación de desbordamiento.
     * @tparam T Tipo de dato (int, float, double, etc.).
     * @param a Primer operando.
     * @param b Segundo operando.
     * @return Resultado de la multiplicación.
     * @throws std::overflow_error en caso de desbordamiento (para tipos enteros).
     */
    template <typename T>
    static T multiply(T a, T b);

    /**
     * @brief Realiza la división de dos valores con validación de errores.
     * @tparam T Tipo de dato (int, float, double, etc.).
     * @param a Numerador.
     * @param b Denominador.
     * @return Resultado de la división.
     * @throws std::invalid_argument si el divisor es cero.
     * @throws std::domain_error si el divisor es demasiado pequeño (para tipos flotantes).
     */
    template <typename T>
    static T divide(T a, T b);
};

#endif // BASIC_OPERATIONS_H
