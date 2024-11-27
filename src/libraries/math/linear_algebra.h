#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>

/**
 * @class LinearAlgebra
 * @brief Módulo de Álgebra Lineal Avanzada en MC++.
 * 
 * Este módulo proporciona operaciones comunes de álgebra lineal, como suma, multiplicación y determinantes,
 * además de utilidades como transposición y normalización de vectores.
 */
class LinearAlgebra {
public:
    /**
     * Realiza la suma de dos matrices.
     * @param matrix1 Primera matriz.
     * @param matrix2 Segunda matriz.
     * @param result Matriz donde se almacenará el resultado de la suma.
     * @throw std::invalid_argument Si las dimensiones de las matrices no coinciden.
     */
    static void matrix_add(const std::vector<std::vector<int>>& matrix1,
                           const std::vector<std::vector<int>>& matrix2,
                           std::vector<std::vector<int>>& result);

    /**
     * Calcula el determinante de una matriz cuadrada.
     * @param matrix Matriz de la cual se calculará el determinante.
     * @return El determinante de la matriz.
     * @throw std::invalid_argument Si la matriz no es cuadrada.
     */
    static int matrix_determinant(const std::vector<std::vector<int>>& matrix);

    /**
     * Realiza la multiplicación de dos matrices.
     * @param matrix1 Primera matriz.
     * @param matrix2 Segunda matriz.
     * @param result Matriz donde se almacenará el resultado de la multiplicación.
     * @throw std::invalid_argument Si las dimensiones de las matrices no son compatibles.
     */
    static void matrix_multiply(const std::vector<std::vector<int>>& matrix1,
                                const std::vector<std::vector<int>>& matrix2,
                                std::vector<std::vector<int>>& result);

    /**
     * Realiza la transposición de una matriz.
     * @param matrix Matriz a transponer.
     * @param result Matriz donde se almacenará la transposición.
     */
    static void matrix_transpose(const std::vector<std::vector<int>>& matrix,
                                 std::vector<std::vector<int>>& result);

    /**
     * Normaliza un vector.
     * @param vector Vector a normalizar.
     * @return Vector normalizado.
     * @throw std::invalid_argument Si el vector tiene magnitud cero.
     */
    static std::vector<float> normalize_vector(const std::vector<float>& vector);

    /**
     * Calcula la inversa de una matriz cuadrada.
     * @param matrix Matriz cuadrada a invertir.
     * @param result Matriz donde se almacenará la inversa.
     * @throw std::invalid_argument Si la matriz no es cuadrada o no es invertible.
     */
    static void matrix_inverse(const std::vector<std::vector<float>>& matrix,
                               std::vector<std::vector<float>>& result);
};

#endif // LINEAR_ALGEBRA_H
