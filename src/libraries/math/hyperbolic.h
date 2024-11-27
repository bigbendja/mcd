#ifndef HYPERBOLIC_H
#define HYPERBOLIC_H

/**
 * @class Hyperbolic
 * @brief Proporciona funciones hiperbólicas avanzadas optimizadas para MC++.
 *
 * Este módulo ofrece métodos para calcular funciones hiperbólicas comunes
 * como sinh, cosh y tanh, manejando valores extremos mediante excepciones.
 */
class Hyperbolic {
public:
    /**
     * @brief Calcula el seno hiperbólico de un ángulo dado.
     * 
     * @param angle Ángulo en radianes.
     * @return float El valor de sinh(angle).
     * @throws std::overflow_error Si el cálculo produce un desbordamiento.
     */
    static float sinh(float angle);

    /**
     * @brief Calcula el coseno hiperbólico de un ángulo dado.
     * 
     * @param angle Ángulo en radianes.
     * @return float El valor de cosh(angle).
     * @throws std::overflow_error Si el cálculo produce un desbordamiento.
     */
    static float cosh(float angle);

    /**
     * @brief Calcula la tangente hiperbólica de un ángulo dado.
     * 
     * @param angle Ángulo en radianes.
     * @return float El valor de tanh(angle).
     * @throws std::overflow_error Si el cálculo produce un desbordamiento.
     */
    static float tanh(float angle);

    // Opcional: Sobrecargas para doble precisión
    /**
     * @brief Sobrecarga para calcular el seno hiperbólico con `double`.
     */
    static double sinh(double angle);

    /**
     * @brief Sobrecarga para calcular el coseno hiperbólico con `double`.
     */
    static double cosh(double angle);

    /**
     * @brief Sobrecarga para calcular la tangente hiperbólica con `double`.
     */
    static double tanh(double angle);
};

#endif // HYPERBOLIC_H
