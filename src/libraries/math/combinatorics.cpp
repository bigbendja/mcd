#include "combinatorics.h"
#include <stdexcept>
#include <limits>  // Para verificar límites de enteros

/**
 * @brief Calcula el factorial de un número entero no negativo.
 * 
 * @param n Número entero no negativo.
 * @return int Resultado del factorial.
 * @throws std::invalid_argument Si el número es negativo.
 * @throws std::overflow_error Si ocurre un desbordamiento.
 */
int Combinatorics::factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Error: factorial no definido para números negativos.");
    }
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        if (result > std::numeric_limits<int>::max() / i) {
            throw std::overflow_error("Error: desbordamiento en el cálculo del factorial.");
        }
        result *= i;
    }
    return result;
}

/**
 * @brief Calcula el número de combinaciones de n elementos tomados de r en r.
 * 
 * @param n Número total de elementos.
 * @param r Número de elementos seleccionados.
 * @return int Número de combinaciones posibles.
 * @throws std::invalid_argument Si los valores no son válidos (n < 0, r < 0 o r > n).
 * @throws std::overflow_error Si ocurre un desbordamiento durante el cálculo.
 */
int Combinatorics::combination(int n, int r) {
    if (n < 0 || r < 0 || r > n) {
        throw std::invalid_argument("Error: valores no válidos para combinación.");
    }
    int numerator = 1;
    int denominator = 1;
    for (int i = 1; i <= r; ++i) {
        if (numerator > std::numeric_limits<int>::max() / (n - i + 1)) {
            throw std::overflow_error("Error: desbordamiento en el cálculo de combinación.");
        }
        numerator *= (n - i + 1);
        denominator *= i;
    }
    return numerator / denominator;
}

/**
 * @brief Calcula el número de permutaciones de n elementos tomados de r en r.
 * 
 * @param n Número total de elementos.
 * @param r Número de elementos seleccionados.
 * @return int Número de permutaciones posibles.
 * @throws std::invalid_argument Si los valores no son válidos (n < 0, r < 0 o r > n).
 * @throws std::overflow_error Si ocurre un desbordamiento durante el cálculo.
 */
int Combinatorics::permutation(int n, int r) {
    if (n < 0 || r < 0 || r > n) {
        throw std::invalid_argument("Error: valores no válidos para permutación.");
    }
    int result = 1;
    for (int i = 0; i < r; ++i) {
        if (result > std::numeric_limits<int>::max() / (n - i)) {
            throw std::overflow_error("Error: desbordamiento en el cálculo de permutación.");
        }
        result *= (n - i);
    }
    return result;
}
