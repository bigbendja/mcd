#include "math.h"
#include <cassert>
#include <cmath>
#include <iostream>

// Función auxiliar para ejecutar pruebas unitarias
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas de funciones aritméticas básicas
void test_basic_arithmetic() {
    run_test("Suma de 3 + 5", mc_math::add(3, 5) == 8);
    run_test("Resta de 10 - 3", mc_math::subtract(10, 3) == 7);
    run_test("Multiplicación de 4 * 7", mc_math::multiply(4, 7) == 28);
    run_test("División de 20 / 4", mc_math::divide(20, 4) == 5);
}

// Pruebas de funciones avanzadas
void test_advanced_math_functions() {
    run_test("Potencia 2^3", mc_math::power(2, 3) == 8);
    run_test("Raíz cuadrada de 16", mc_math::sqrt(16) == 4);
    run_test("Logaritmo natural de e", std::abs(mc_math::ln(M_E) - 1) < 1e-6);
}

// Pruebas de trigonometría
void test_trigonometry() {
    run_test("Seno de π/2", std::abs(mc_math::sin(M_PI / 2) - 1) < 1e-6);
    run_test("Coseno de π", std::abs(mc_math::cos(M_PI) + 1) < 1e-6);
    run_test("Tangente de π/4", std::abs(mc_math::tan(M_PI / 4) - 1) < 1e-6);
}

// Pruebas de funciones hiperbólicas
void test_hyperbolic_functions() {
    run_test("Seno hiperbólico de 0", mc_math::sinh(0) == 0);
    run_test("Coseno hiperbólico de 0", mc_math::cosh(0) == 1);
}

// Pruebas de funciones estadísticas
void test_statistics_functions() {
    std::vector<double> values = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    run_test("Media de valores", std::abs(mc_math::mean(values) - 5.0) < 1e-6);
    run_test("Desviación estándar de valores", std::abs(mc_math::standard_deviation(values) - 2.0) < 1e-6);
}

// Pruebas de funciones geométricas
void test_geometry_functions() {
    run_test("Área de círculo con radio 3", std::abs(mc_math::circle_area(3) - (M_PI * 9)) < 1e-6);
    run_test("Perímetro de círculo con radio 3", std::abs(mc_math::circle_perimeter(3) - (2 * M_PI * 3)) < 1e-6);
}

// Pruebas de funciones de álgebra lineal
void test_linear_algebra_functions() {
    std::vector<double> vector1 = {1.0, 2.0, 3.0};
    std::vector<double> vector2 = {4.0, 5.0, 6.0};
    run_test("Producto escalar de vectores", mc_math::dot_product(vector1, vector2) == 32.0);
    auto cross_product_result = mc_math::cross_product(vector1, vector2);
    run_test("Producto cruz de vectores", cross_product_result == std::vector<double>{-3.0, 6.0, -3.0});
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'math'" << std::endl;

    test_basic_arithmetic();
    test_advanced_math_functions();
    test_trigonometry();
    test_hyperbolic_functions();
    test_statistics_functions();
    test_geometry_functions();
    test_linear_algebra_functions();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
