#include "linear_algebra.h"
#include <stdexcept>
#include <vector>

// Adición de matrices
void LinearAlgebra::matrix_add(const std::vector<std::vector<int>>& matrix1,
                               const std::vector<std::vector<int>>& matrix2,
                               std::vector<std::vector<int>>& result) {
    int rows = matrix1.size();
    int cols = matrix1[0].size();

    if (rows != matrix2.size() || cols != matrix2[0].size()) {
        throw std::invalid_argument("Error: Las dimensiones de las matrices no coinciden para la adición.");
    }

    result.resize(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// Determinante de matriz cuadrada
int LinearAlgebra::matrix_determinant(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    if (n != matrix[0].size()) {
        throw std::invalid_argument("Error: La matriz debe ser cuadrada para calcular el determinante.");
    }

    if (n == 1) return matrix[0][0];
    if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    // Implementación recursiva para determinantes pequeños
    int det = 0;
    for (int col = 0; col < n; col++) {
        std::vector<std::vector<int>> submatrix(n - 1, std::vector<int>(n - 1));
        for (int i = 1; i < n; i++) {
            int sub_col = 0;
            for (int j = 0; j < n; j++) {
                if (j == col) continue;
                submatrix[i - 1][sub_col] = matrix[i][j];
                sub_col++;
            }
        }
        det += ((col % 2 == 0) ? 1 : -1) * matrix[0][col] * matrix_determinant(submatrix);
    }
    return det;
}

// Multiplicación de matrices
void LinearAlgebra::matrix_multiply(const std::vector<std::vector<int>>& matrix1,
                                    const std::vector<std::vector<int>>& matrix2,
                                    std::vector<std::vector<int>>& result) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        throw std::invalid_argument("Error: Dimensiones incompatibles para multiplicación.");
    }

    result.resize(rows1, std::vector<int>(cols2, 0));
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Transposición de matriz
void LinearAlgebra::matrix_transpose(const std::vector<std::vector<int>>& matrix,
                                     std::vector<std::vector<int>>& result) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    result.resize(cols, std::vector<int>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}
