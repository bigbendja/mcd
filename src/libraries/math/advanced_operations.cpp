#include "advanced_operations.h"
#include <cmath>
#include <stdexcept>
#include <limits>

/**
 * @brief Eleva un número a una potencia de forma segura, evitando desbordamientos.
 * 
 * @tparam T Tipo de dato (int, float, double, etc.).
 * @param base Base de la potencia.
 * @param exponent Exponente al cual elevar la base.
 * @return T Resultado de la potencia.
 * @throws std::overflow_error Si ocurre un desbordamiento durante la operación (para tipos enteros).
 * @throws std::invalid_argument Si el exponente es negativo y el tipo es entero.
 */
template <typename T>
T AdvancedOperations::exponentiate(T base, int exponent) {
    if constexpr (std::is_integral_v<T>) {
        if (exponent < 0) {
            throw std::invalid_argument("Error: Exponente negativo no soportado en enteros.");
        }
        T result = 1;
        for (int i = 0; i < exponent; ++i) {
            if (result > std::numeric_limits<T>::max() / base) {
                throw std::overflow_error("Error: Desbordamiento en exponenciación.");
            }
            result *= base;
        }
        return result;
    } else {
        return std::pow(base, exponent);
    }
}

/**
 * @brief Calcula la raíz cuadrada de un número de forma segura.
 * 
 * @tparam T Tipo de dato (int, float, double, etc.).
 * @param number Número del cual calcular la raíz cuadrada.
 * @return T Resultado de la raíz cuadrada.
 * @throws std::invalid_argument Si el número es negativo.
 */
template <typename T>
T AdvancedOperations::sqrt(T number) {
    if (number < static_cast<T>(0)) {
        throw std::invalid_argument("Error: Número negativo en cálculo de raíz cuadrada.");
    }
    return std::sqrt(number);
}

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
T AdvancedOperations::log_base_n(T value, T base) {
    if (value <= static_cast<T>(0) || base <= static_cast<T>(0) || base == static_cast<T>(1)) {
        throw std::invalid_argument("Error: Valores inválidos para logaritmo.");
    }
    return std::log(value) / std::log(base);
}

// Es necesario incluir las instanciaciones explícitas para cada tipo que se usará.
template int AdvancedOperations::exponentiate<int>(int, int);
template float AdvancedOperations::exponentiate<float>(float, int);
template double AdvancedOperations::exponentiate<double>(double, int);

template int AdvancedOperations::sqrt<int>(int);
template float AdvancedOperations::sqrt<float>(float);
template double AdvancedOperations::sqrt<double>(double);

template float AdvancedOperations::log_base_n<float>(float, float);
template double AdvancedOperations::log_base_n<double>(double, double);
