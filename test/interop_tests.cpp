#include "interop.h"
#include "python_interface_advanced.h"
#include "cpp_interface_advanced.h"
#include "rust_interface_advanced.h"
#include <cassert>
#include <iostream>

// Función auxiliar para ejecutar pruebas y verificar los resultados
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas para la interfaz Python
void test_python_integration() {
    interop::PythonInterface pyInterface;
    bool init_result = pyInterface.initialize();
    run_test("Inicialización de la interfaz Python", init_result);

    std::string result = pyInterface.executeScript("print('Hello from Python')");
    run_test("Ejecución de script Python", result.find("Hello from Python") != std::string::npos);
    
    pyInterface.finalize();
    run_test("Finalización de la interfaz Python", true);
}

// Pruebas para la interfaz C++
void test_cpp_integration() {
    interop::CppInterface cppInterface;
    bool init_result = cppInterface.initialize();
    run_test("Inicialización de la interfaz C++", init_result);

    int result = cppInterface.executeFunction([]() { return 42; });
    run_test("Ejecución de función C++", result == 42);
    
    cppInterface.finalize();
    run_test("Finalización de la interfaz C++", true);
}

// Pruebas para la interfaz Rust
void test_rust_integration() {
    interop::RustInterface rustInterface;
    bool init_result = rustInterface.initialize();
    run_test("Inicialización de la interfaz Rust", init_result);

    int result = rustInterface.callFunction("calculate_sum", {10, 20});
    run_test("Ejecución de función Rust", result == 30);
    
    rustInterface.finalize();
    run_test("Finalización de la interfaz Rust", true);
}

// Pruebas de conversión de tipos entre lenguajes
void test_type_conversion() {
    int integer_val = interop::convertTo<int>("42");
    run_test("Conversión de string a int", integer_val == 42);

    std::string str_val = interop::convertTo<std::string>(3.14159);
    run_test("Conversión de float a string", str_val.find("3.14159") != std::string::npos);
}

// Pruebas de configuración de interop
void test_interop_configuration() {
    config::load_config("./config/interop_config.json");

    std::string python_path = config::get_setting<std::string>("python_interpreter_path");
    run_test("Ruta del intérprete Python configurada", !python_path.empty());

    std::string cpp_compiler = config::get_setting<std::string>("cpp_compiler_path");
    run_test("Ruta del compilador C++ configurada", !cpp_compiler.empty());
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'interop'" << std::endl;

    test_python_integration();
    test_cpp_integration();
    test_rust_integration();
    test_type_conversion();
    test_interop_configuration();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
