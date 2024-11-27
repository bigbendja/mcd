#include "string_utils.h"
#include <cassert>
#include <iostream>

// Función auxiliar para ejecutar y mostrar resultados de pruebas unitarias
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas para toLower y toUpper
void test_case_conversion() {
    run_test("Convertir a minúsculas", mc_utils::StringUtils::toLower("HELLO") == "hello");
    run_test("Convertir a mayúsculas", mc_utils::StringUtils::toUpper("hello") == "HELLO");
}

// Prueba de división de cadena
void test_split() {
    auto tokens = mc_utils::StringUtils::split("one,two,three", ',');
    run_test("Dividir cadena en tokens - tamaño", tokens.size() == 3);
    run_test("Dividir cadena en tokens - token1", tokens[0] == "one");
    run_test("Dividir cadena en tokens - token2", tokens[1] == "two");
    run_test("Dividir cadena en tokens - token3", tokens[2] == "three");
}

// Prueba de unión de cadena
void test_join() {
    std::vector<std::string> tokens = {"one", "two", "three"};
    run_test("Unir tokens en cadena", mc_utils::StringUtils::join(tokens, ',') == "one,two,three");
}

// Pruebas para trim
void test_trim() {
    run_test("Eliminar espacios en blanco - inicial y final", mc_utils::StringUtils::trim("   hello   ") == "hello");
    run_test("Eliminar espacios en blanco - sin cambio", mc_utils::StringUtils::trim("hello") == "hello");
}

// Prueba de reemplazo de subcadenas
void test_replaceAll() {
    run_test("Reemplazar subcadena", mc_utils::StringUtils::replaceAll("hello world", "world", "MC++") == "hello MC++");
    run_test("Reemplazar todas las ocurrencias", mc_utils::StringUtils::replaceAll("aaa", "a", "b") == "bbb");
}

// Pruebas para startsWith y endsWith
void test_startsWith_endsWith() {
    run_test("Comienza con subcadena - positivo", mc_utils::StringUtils::startsWith("hello world", "hello"));
    run_test("Comienza con subcadena - negativo", !mc_utils::StringUtils::startsWith("hello world", "world"));
    run_test("Termina con subcadena - positivo", mc_utils::StringUtils::endsWith("hello world", "world"));
    run_test("Termina con subcadena - negativo", !mc_utils::StringUtils::endsWith("hello world", "hello"));
}

// Prueba de conversión con precisión decimal
void test_toStringWithPrecision() {
    run_test("Convertir a cadena con precisión - 2 decimales", mc_utils::StringUtils::toStringWithPrecision(3.14159, 2) == "3.14");
    run_test("Convertir a cadena con precisión - 3 decimales", mc_utils::StringUtils::toStringWithPrecision(1.56789, 3) == "1.568");
}

int main() {
    std::cout << "Iniciando pruebas para la funcionalidad de manejo de cadenas" << std::endl;

    test_case_conversion();
    test_split();
    test_join();
    test_trim();
    test_replaceAll();
    test_startsWith_endsWith();
    test_toStringWithPrecision();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
