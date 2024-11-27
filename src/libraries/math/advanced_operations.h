#ifndef ADVANCED_OPERATIONS_H
#define ADVANCED_OPERATIONS_H

#include <type_traits>
#include <stdexcept>

/**
 * @class AdvancedOperations
 * @brief Clase genérica para realizar operaciones matemáticas avanzadas como exponenciación, raíces cuadradas y logaritmos.
 *
 * Esta clase está diseñada para operar con múltiples tipos de datos (int, float, double, etc.) con validaciones integradas
 * y manejo seguro de excepciones.
 */
class AdvancedOperations {
public:
    /**
     * @brief Calcula la potencia de una base elevada a un exponente.
     * 
     * @tparam T Tipo de dato (int, float, double, etc.).
     * @param base Base de la potencia.
     * @param exponent Exponente al cual elevar la base.
     * @return T Resultado de la potencia.
     * @throws std::overflow_error Si ocurre un desbordamiento (para tipos enteros).
     * @throws std::invalid_argument Si el exponente es negativo y el tipo es entero.
     */
    template <typename T>
    static T exponentiate(T base, int exponent);

    /**
     * @brief Calcula la raíz cuadrada de un número.
     * 
     * @tparam T Tipo de dato (int, float, double, etc.).
     * @param number Número del cual calcular la raíz cuadrada.
     * @return T Resultado de la raíz cuadrada.
     * @throws std::invalid_argument Si el número es negativo.
     */
    template <typename T>
    static T sqrt(T number);

    /**
     * @brief Calcula el logaritmo de un valor en una base específica.
     * 
     * @tparam T Tipo de dato (float, double, etc.).
     * @param value Valor del cual calcular el logaritmo.
     * @param base Base del logaritmo.
     * @return T Resultado del logaritmo en la base especificada.
     * @throws std::invalid_argument Si el valor o la base son inválidos (valor <= 0, base <= 0 o base == 1).
     */
    template <typename T>
    static T log_base_n(T value, T base);
};

#endif // ADVANCED_OPERATIONS_H
