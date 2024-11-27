#include "linear_algebra_advanced.h"
#include <stdexcept>
#include <vector>
#include <limits>

/**
 * @brief Multiplica dos matrices.
 * @param matrix1 Primera matriz.
 * @param matrix2 Segunda matriz.
 * @param result Matriz donde se almacenará el resultado.
 * @throw std::invalid_argument Si las dimensiones de las matrices no son compatibles.
 */
void LinearAlgebraAdvanced::matrix_multiply(const std::vector<std::vector<float>>& matrix1,
                                            const std::vector<std::vector<float>>& matrix2,
                                            std::vector<std::vector<float>>& result) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        throw std::invalid_argument("Error: Las dimensiones de las matrices no permiten la multiplicación.");
    }

    result.assign(rows1, std::vector<float>(cols2, 0));
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

/**
 * @brief Realiza la descomposición LU de una matriz.
 * @param matrix Matriz de entrada.
 * @param L Matriz triangular inferior.
 * @param U Matriz triangular superior.
 * @throw std::runtime_error Si el pivote es cero.
 */
void LinearAlgebraAdvanced::matrix_lu_decomposition(const std::vector<std::vector<float>>& matrix,
                                                    std::vector<std::vector<float>>& L,
                                                    std::vector<std::vector<float>>& U) {
    int size = matrix.size();

    L.assign(size, std::vector<float>(size, 0));
    U.assign(size, std::vector<float>(size, 0));

    for (int i = 0; i < size; i++) {
        for (int k = i; k < size; k++) {
            float sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = matrix[i][k] - sum;
        }

        for (int k = i; k < size; k++) {
            if (i == k) {
                L[i][i] = 1.0f;
            } else {
                float sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += L[k][j] * U[j][i];
                }
                if (U[i][i] == 0) {
                    throw std::runtime_error("Error: Descomposición LU fallida, pivote cero encontrado.");
                }
                L[k][i] = (matrix[k][i] - sum) / U[i][i];
            }
        }
    }
}

/**
 * @brief Calcula la inversa de una matriz cuadrada usando descomposición LU.
 * @param matrix Matriz de entrada.
 * @param result Matriz inversa.
 * @throw std::invalid_argument Si la matriz no es cuadrada.
 * @throw std::runtime_error Si la matriz no es invertible.
 */
void LinearAlgebraAdvanced::matrix_inverse(const std::vector<std::vector<float>>& matrix,
                                           std::vector<std::vector<float>>& result) {
    int size = matrix.size();
    if (size == 0 || matrix[0].size() != size) {
        throw std::invalid_argument("Error: La matriz debe ser cuadrada para calcular la inversa.");
    }

    std::vector<std::vector<float>> L, U;
    matrix_lu_decomposition(matrix, L, U);

    result.assign(size, std::vector<float>(size, 0));
    std::vector<std::vector<float>> identity(size, std::vector<float>(size, 0));
    for (int i = 0; i < size; i++) {
        identity[i][i] = 1.0f;
    }

    // Resolver Ly = I (hacia adelante)
    std::vector<std::vector<float>> Y(size, std::vector<float>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L[i][k] * Y[k][j];
            }
            Y[i][j] = identity[i][j] - sum;
        }
    }

    // Resolver Ux = y (hacia atrás)
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < size; j++) {
            float sum = 0;
            for (int k = i + 1; k < size; k++) {
                sum += U[i][k] * result[k][j];
            }
            if (U[i][i] == 0) {
                throw std::runtime_error("Error: Matriz no invertible, pivote cero encontrado.");
            }
            result[i][j] = (Y[i][j] - sum) / U[i][i];
        }
    }
}
