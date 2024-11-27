#include "hyperbolic.h"
#include <cmath>
#include <limits>
#include <stdexcept>

/**
 * @brief Calcula el seno hiperbólico de un ángulo en radianes.
 * 
 * @param angle Ángulo en radianes.
 * @return float Resultado de sinh(angle).
 * @throws std::overflow_error Si el resultado es infinito.
 */
float Hyperbolic::sinh(float angle) {
    float result = std::sinh(angle);
    if (std::isinf(result)) {
        throw std::overflow_error("Error: Desbordamiento en cálculo de sinh.");
    }
    return result;
}

/**
 * @brief Calcula el coseno hiperbólico de un ángulo en radianes.
 * 
 * @param angle Ángulo en radianes.
 * @return float Resultado de cosh(angle).
 * @throws std::overflow_error Si el resultado es infinito.
 */
float Hyperbolic::cosh(float angle) {
    float result = std::cosh(angle);
    if (std::isinf(result)) {
        throw std::overflow_error("Error: Desbordamiento en cálculo de cosh.");
    }
    return result;
}

/**
 * @brief Calcula la tangente hiperbólica de un ángulo en radianes.
 * 
 * @param angle Ángulo en radianes.
 * @return float Resultado de tanh(angle).
 * @throws std::overflow_error Si el resultado es infinito.
 */
float Hyperbolic::tanh(float angle) {
    float result = std::tanh(angle);
    if (std::isinf(result)) {
        throw std::overflow_error("Error: Desbordamiento en cálculo de tanh.");
    }
    return result;
}
