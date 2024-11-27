#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "basic_operations.h"
#include "advanced_operations.h"
#include "linear_algebra_advanced.h"
#include "trigonometry.h"

// Función auxiliar para registrar resultados de pruebas
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas de operaciones básicas
void test_basic_operations() {
    run_test("Addition (5 + 3 == 8)", BasicOperations::add(5, 3) == 8);
    run_test("Subtraction (10 - 4 == 6)", BasicOperations::subtract(10, 4) == 6);
    run_test("Multiplication (3 * 7 == 21)", BasicOperations::multiply(3, 7) == 21);

    try {
        run_test("Division (21 / 7 == 3)", BasicOperations::divide(21, 7) == 3.0f);
        BasicOperations::divide(5, 0); // Esto debería lanzar una excepción
        run_test("Division by zero throws exception", false);
    } catch (const std::invalid_argument&) {
        run_test("Division by zero throws exception", true);
    }
}

// Pruebas de operaciones avanzadas
void test_advanced_operations() {
    run_test("Exponentiation (2^8 == 256)", AdvancedOperations::exponentiate(2, 8) == 256);
    run_test("Square Root (sqrt(49) == 7)", AdvancedOperations::sqrt(49) == 7.0f);
    run_test("Logarithm (log2(1024) == 10)", std::abs(AdvancedOperations::log_base_n(1024, 2) - 10.0f) < 0.0001);
}

// Pruebas de álgebra lineal avanzada
void test_linear_algebra_operations() {
    std::vector<std::vector<int>> matrix1 = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> matrix2 = {{2, 0}, {1, 2}};
    std::vector<std::vector<int>> result;

    LinearAlgebraAdvanced::matrix_multiply(matrix1, matrix2, result);
    run_test("Matrix Multiplication (2x2)", result == std::vector<std::vector<int>>{{4, 4}, {10, 8}});

    std::vector<std::vector<int>> L, U;
    LinearAlgebraAdvanced::matrix_lu_decomposition(matrix1, L, U);
    run_test("LU Decomposition", L.size() == 2 && U.size() == 2);
}

// Pruebas de trigonometría
void test_trigonometry() {
    run_test("Sine (sin(0.5))", std::abs(Trigonometry::sin(0.5) - std::sin(0.5)) < 0.0001);
    run_test("Cosine (cos(0.5))", std::abs(Trigonometry::cos(0.5) - std::cos(0.5)) < 0.0001);

    try {
        Trigonometry::tan(3.14159 / 2); // Esto debería lanzar una excepción
        run_test("Tangent undefined throws exception", false);
    } catch (const std::invalid_argument&) {
        run_test("Tangent undefined throws exception", true);
    }
}

// Función principal de pruebas
int main() {
    std::cout << "Iniciando pruebas para la biblioteca matemática MC++...\n";

    test_basic_operations();
    test_advanced_operations();
    test_linear_algebra_operations();
    test_trigonometry();

    std::cout << "Pruebas completadas.\n";
    return 0;
}
