#include "trigonometry.h"
#include <cmath>
#include <stdexcept>

// Tolerancia para manejar valores cercanos a cero
constexpr float TOLERANCE = 1e-9;

/**
 * @brief Calcula el seno de un ángulo dado en radianes.
 * @param angle Ángulo en radianes.
 * @return Valor del seno del ángulo.
 */
float Trigonometry::sin(float angle) {
    return std::sin(angle);
}

/**
 * @brief Calcula el coseno de un ángulo dado en radianes.
 * @param angle Ángulo en radianes.
 * @return Valor del coseno del ángulo.
 */
float Trigonometry::cos(float angle) {
    return std::cos(angle);
}

/**
 * @brief Calcula la tangente de un ángulo dado en radianes.
 * @param angle Ángulo en radianes.
 * @return Valor de la tangente del ángulo.
 * @throws std::invalid_argument Si el coseno del ángulo es cero (tangente indefinida).
 */
float Trigonometry::tan(float angle) {
    float cos_value = std::cos(angle);
    if (std::fabs(cos_value) < TOLERANCE) {
        throw std::invalid_argument("Error: Tangente indefinida para este ángulo (coseno es cero).");
    }
    return std::sin(angle) / cos_value;
}
