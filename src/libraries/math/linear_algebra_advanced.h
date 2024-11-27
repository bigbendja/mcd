#ifndef LINEAR_ALGEBRA_ADVANCED_H
#define LINEAR_ALGEBRA_ADVANCED_H

#include <vector>

/**
 * @file linear_algebra_advanced.h
 * @brief Declaración de funciones avanzadas para álgebra lineal en MC++.
 * 
 * Este módulo proporciona operaciones como multiplicación de matrices,
 * cálculo de inversas y descomposición LU, optimizadas para aplicaciones de alto rendimiento.
 */

class LinearAlgebraAdvanced {
public:
    /**
     * @brief Multiplica dos matrices.
     * 
     * @param matrix1 Primer operando, una matriz de números en coma flotante.
     * @param matrix2 Segundo operando, una matriz de números en coma flotante.
     * @param result Matriz de salida donde se almacenará el resultado.
     * @throws std::invalid_argument Si las dimensiones no permiten la multiplicación.
     */
    static void matrix_multiply(const std::vector<std::vector<float>>& matrix1,
                                 const std::vector<std::vector<float>>& matrix2,
                                 std::vector<std::vector<float>>& result);

    /**
     * @brief Calcula la inversa de una matriz cuadrada.
     * 
     * @param matrix Matriz de entrada, debe ser cuadrada.
     * @param result Matriz de salida donde se almacenará la inversa.
     * @throws std::invalid_argument Si la matriz no es cuadrada.
     * @throws std::runtime_error Si la matriz es singular y no tiene inversa.
     */
    static void matrix_inverse(const std::vector<std::vector<float>>& matrix,
                                std::vector<std::vector<float>>& result);

    /**
     * @brief Realiza la descomposición LU de una matriz cuadrada.
     * 
     * @param matrix Matriz de entrada, debe ser cuadrada.
     * @param L Matriz triangular inferior de salida.
     * @param U Matriz triangular superior de salida.
     * @throws std::invalid_argument Si la matriz no es cuadrada.
     * @throws std::runtime_error Si se encuentra un pivote cero.
     */
    static void matrix_lu_decomposition(const std::vector<std::vector<float>>& matrix,
                                        std::vector<std::vector<float>>& L,
                                        std::vector<std::vector<float>>& U);
};

#endif // LINEAR_ALGEBRA_ADVANCED_H
