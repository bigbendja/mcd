#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

/**
 * @file trigonometry.h
 * @brief Módulo Trigonometry en MC++: Funciones trigonométricas avanzadas y seguras.
 *
 * Este módulo incluye funciones para calcular el seno, coseno y tangente,
 * con manejo de errores en cálculos que podrían ser indefinidos.
 */

class Trigonometry {
public:
    /**
     * @brief Calcula el seno de un ángulo en radianes.
     * @param angle Ángulo en radianes.
     * @return Valor del seno del ángulo.
     */
    static float sin(float angle);

    /**
     * @brief Calcula el coseno de un ángulo en radianes.
     * @param angle Ángulo en radianes.
     * @return Valor del coseno del ángulo.
     */
    static float cos(float angle);

    /**
     * @brief Calcula la tangente de un ángulo en radianes.
     * @param angle Ángulo en radianes.
     * @return Valor de la tangente del ángulo.
     * @throws std::invalid_argument Si el coseno del ángulo es cero (tangente indefinida).
     */
    static float tan(float angle);

private:
    /**
     * @brief Tolerancia para determinar valores cercanos a cero en cálculos trigonométricos.
     */
    static constexpr float TOLERANCE = 1e-9;
};

#endif // TRIGONOMETRY_H
