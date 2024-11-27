#include "cpp_interface_advanced.h"
#include <iostream>
#include <cassert>

void testCreateCppEnvironment() {
    // Prueba para crear un entorno válido
    assert(CREATE_CPP_ENVIRONMENT("env1", "/usr/bin/g++"));
    std::cout << "testCreateCppEnvironment PASSED" << std::endl;

    // Prueba para evitar duplicados
    try {
        CREATE_CPP_ENVIRONMENT("env1", "/usr/bin/g++");
    } catch (const std::runtime_error& e) {
        std::cout << "testCreateCppEnvironment DUPLICATE PASSED" << std::endl;
    }
}

void testInitializeCppEnvironment() {
    // Crear entorno antes de inicializar
    CREATE_CPP_ENVIRONMENT("env2", "/usr/bin/g++");

    // Inicializar entorno válido
    assert(INITIALIZE_CPP_ENVIRONMENT("env2"));
    std::cout << "testInitializeCppEnvironment PASSED" << std::endl;
}

void testExecuteCppFile() {
    // Crear y inicializar entorno
    CREATE_CPP_ENVIRONMENT("env3", "/usr/bin/g++");
    INITIALIZE_CPP_ENVIRONMENT("env3");

    // Simular ejecución de archivo válido
    assert(EXECUTE_CPP_FILE("env3", "test_program.cpp", "test_output"));
    std::cout << "testExecuteCppFile PASSED" << std::endl;

    // Probar ejecución con extensión no válida
    try {
        EXECUTE_CPP_FILE("env3", "test_program.txt", "test_output");
    } catch (const std::invalid_argument& e) {
        std::cout << "testExecuteCppFile INVALID EXTENSION PASSED" << std::endl;
    }
}

void testPassDataToCpp() {
    // Crear y inicializar entorno
    CREATE_CPP_ENVIRONMENT("env4", "/usr/bin/g++");
    INITIALIZE_CPP_ENVIRONMENT("env4");

    // Pasar datos válidos
    std::vector<std::string> args = {"arg1", "arg2"};
    assert(PASS_DATA_TO_CPP("env4", args));
    std::cout << "testPassDataToCpp PASSED" << std::endl;
}

void testRetrieveOutputFromCpp() {
    // Crear y inicializar entorno
    CREATE_CPP_ENVIRONMENT("env5", "/usr/bin/g++");
    INITIALIZE_CPP_ENVIRONMENT("env5");

    // Simular recuperación de datos
    std::string output = RETRIEVE_OUTPUT_FROM_CPP("env5", "test_output");
    assert(!output.empty());
    std::cout << "testRetrieveOutputFromCpp PASSED" << std::endl;
}

void testCloseCppEnvironment() {
    // Crear e inicializar entorno
    CREATE_CPP_ENVIRONMENT("env6", "/usr/bin/g++");
    INITIALIZE_CPP_ENVIRONMENT("env6");

    // Cerrar entorno
    assert(CLOSE_CPP_ENVIRONMENT("env6"));
    std::cout << "testCloseCppEnvironment PASSED" << std::endl;

    // Intentar cerrar un entorno inexistente
    try {
        CLOSE_CPP_ENVIRONMENT("env6");
    } catch (const std::runtime_error& e) {
        std::cout << "testCloseCppEnvironment NON-EXISTENT PASSED" << std::endl;
    }
}

void testListActiveCppEnvironments() {
    // Crear y inicializar varios entornos
    CREATE_CPP_ENVIRONMENT("env7", "/usr/bin/g++");
    INITIALIZE_CPP_ENVIRONMENT("env7");

    CREATE_CPP_ENVIRONMENT("env8", "/usr/bin/g++");
    INITIALIZE_CPP_ENVIRONMENT("env8");

    // Listar entornos activos
    auto active_envs = LIST_ACTIVE_CPP_ENVIRONMENTS();
    assert(active_envs.size() == 2);
    std::cout << "testListActiveCppEnvironments PASSED" << std::endl;
}

int main() {
    try {
        testCreateCppEnvironment();
        testInitializeCppEnvironment();
        testExecuteCppFile();
        testPassDataToCpp();
        testRetrieveOutputFromCpp();
        testCloseCppEnvironment();
        testListActiveCppEnvironments();
        std::cout << "All tests PASSED successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test FAILED: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
