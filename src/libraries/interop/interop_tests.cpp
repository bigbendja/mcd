#include "cpp_interface_advanced.h"
#include "python_interface_advanced.h"
#include "rust_interface_advanced.h"
#include "data_conversion_advanced.h"
#include <iostream>
#include <cassert>
#include <vector>

// Función auxiliar para ejecutar y registrar resultados de pruebas
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas para `cpp_interface_advanced`
void testCppInterface() {
    try {
        assert(CREATE_CPP_ENVIRONMENT("test_env", "/usr/bin/g++"));
        run_test("Crear entorno C++", true);

        assert(INITIALIZE_CPP_ENVIRONMENT("test_env"));
        run_test("Inicializar entorno C++", true);

        bool load_result = LOAD_CPP_LIBRARY("test_env", "/path/to/sample_library.so");
        run_test("Cargar biblioteca válida en entorno C++", load_result);

        bool exec_result = EXECUTE_CPP_FILE("test_env", "valid_source.cpp", "output_binary");
        run_test("Ejecutar archivo fuente válido en entorno C++", exec_result);

        bool pass_data_result = PASS_DATA_TO_CPP("test_env", {"arg1", "arg2", "arg3"});
        run_test("Pasar datos a entorno C++", pass_data_result);

        bool integrity_result = VERIFY_CPP_ENVIRONMENT_INTEGRITY("test_env");
        run_test("Verificar integridad del entorno C++", integrity_result);

        assert(CLOSE_CPP_ENVIRONMENT("test_env"));
        run_test("Cerrar entorno C++", true);
    } catch (const std::exception& e) {
        std::cerr << "Error en testCppInterface: " << e.what() << std::endl;
        run_test("testCppInterface", false);
    }
}

// Pruebas para `python_interface_advanced`
void testPythonInterface() {
    try {
        assert(CREATE_PYTHON_ENVIRONMENT("test_py_env"));
        run_test("Crear entorno Python", true);

        assert(INITIALIZE_PYTHON_ENVIRONMENT("test_py_env"));
        run_test("Inicializar entorno Python", true);

        assert(LOAD_PYTHON_MODULE("test_py_env", "math"));
        run_test("Cargar módulo Python (math)", true);

        auto result = EXECUTE_PYTHON_FUNCTION("test_py_env", "math", "sqrt", {16}, {});
        run_test("Ejecutar función Python (sqrt)", result == 4.0);

        bool integrity_result = VERIFY_ENVIRONMENT_INTEGRITY("test_py_env");
        run_test("Verificar integridad del entorno Python", integrity_result);

        assert(CLOSE_PYTHON_ENVIRONMENT("test_py_env"));
        run_test("Cerrar entorno Python", true);
    } catch (const std::exception& e) {
        std::cerr << "Error en testPythonInterface: " << e.what() << std::endl;
        run_test("testPythonInterface", false);
    }
}

// Pruebas para `rust_interface_advanced`
void testRustInterface() {
    try {
        assert(CREATE_RUST_ENVIRONMENT("test_rust_env"));
        run_test("Crear entorno Rust", true);

        assert(INITIALIZE_RUST_ENVIRONMENT("test_rust_env"));
        run_test("Inicializar entorno Rust", true);

        assert(LOAD_RUST_LIBRARY("test_rust_env", "/path/to/data_analysis_lib"));
        run_test("Cargar biblioteca Rust", true);

        auto result = CALL_RUST_FUNCTION("data_analysis_lib", "process_data", {5, 10, 15});
        run_test("Ejecutar función Rust (process_data)", result == 30.0);

        bool integrity_result = VERIFY_RUST_ENVIRONMENT_INTEGRITY("test_rust_env");
        run_test("Verificar integridad del entorno Rust", integrity_result);

        assert(CLOSE_RUST_ENVIRONMENT("test_rust_env"));
        run_test("Cerrar entorno Rust", true);
    } catch (const std::exception& e) {
        std::cerr << "Error en testRustInterface: " << e.what() << std::endl;
        run_test("testRustInterface", false);
    }
}

// Pruebas para funciones cruzadas entre lenguajes
void testCrossLanguageFunctions() {
    try {
        CREATE_CPP_ENVIRONMENT("cross_env", "/usr/bin/g++");
        INITIALIZE_CPP_ENVIRONMENT("cross_env");

        bool python_result = EXECUTE_CROSS_LANGUAGE_FUNCTION("cross_env", "python", "some_python_function", {"arg1", "arg2"});
        run_test("Función cruzada (Python)", python_result);

        bool cpp_result = EXECUTE_CROSS_LANGUAGE_FUNCTION("cross_env", "cpp", "valid_source.cpp", {});
        run_test("Función cruzada (C++)", cpp_result);

        bool rust_result = EXECUTE_CROSS_LANGUAGE_FUNCTION("cross_env", "rust", "some_rust_function", {"arg1"});
        run_test("Función cruzada (Rust)", rust_result);

        CLOSE_CPP_ENVIRONMENT("cross_env");
    } catch (const std::exception& e) {
        std::cerr << "Error en testCrossLanguageFunctions: " << e.what() << std::endl;
        run_test("testCrossLanguageFunctions", false);
    }
}

// Pruebas para conversiones de datos
void testDataConversions() {
    try {
        auto json_data = TO_JSON({{"key", "value"}});
        auto data_from_json = FROM_JSON(json_data);
        run_test("Conversión JSON", data_from_json["key"] == "value");

        auto csv_data = TO_CSV({{"name", "MC++"}, {"type", "interop"}});
        auto data_from_csv = FROM_CSV(csv_data);
        run_test("Conversión CSV", data_from_csv[0]["name"] == "MC++");

        run_test("Conversión número a cadena", NUMBER_TO_STRING(123.456) == "123.456");
        run_test("Conversión cadena a número", STRING_TO_NUMBER("123.456") == 123.456);
    } catch (const std::exception& e) {
        std::cerr << "Error en testDataConversions: " << e.what() << std::endl;
        run_test("testDataConversions", false);
    }
}

// Pruebas para configuración intermodular
void testInteropConfig() {
    try {
        bool config_result = SET_INTEROP_CONFIG("python", "max_runtime_ms", 5000);
        run_test("Configurar parámetro (Python)", config_result);
    } catch (const std::exception& e) {
        std::cerr << "Error en testInteropConfig: " << e.what() << std::endl;
        run_test("testInteropConfig", false);
    }
}

int main() {
    std::cout << "Iniciando pruebas para la librería `interop`..." << std::endl;

    testCppInterface();
    testPythonInterface();
    testRustInterface();
    testCrossLanguageFunctions();
    testDataConversions();
    testInteropConfig();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
