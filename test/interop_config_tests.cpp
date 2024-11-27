#include "interop_config.h"
#include <iostream>
#include <cassert>
#include <filesystem>

void validateInteropConfig() {
    std::cout << "Validando configuración de interop..." << std::endl;

    try {
        // Validar rutas
        assert(std::filesystem::exists("/usr/bin/python3"));
        assert(std::filesystem::exists("/usr/bin/g++"));
        assert(std::filesystem::exists("/usr/bin/rustc"));

        // Validar módulos permitidos
        assert(isModuleAllowed("numpy"));
        assert(isModuleAllowed("math"));
        assert(!isModuleAllowed("random_unallowed"));

        // Validar restricciones de rendimiento
        assert(getMaxRuntimeMs() == 3000);
        assert(getMemoryLimitMb() == 512);

        std::cout << "[PASSED] Validación de configuración de interop completada." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[FAILED] Validación de configuración fallida: " << e.what() << std::endl;
    }
}

int main() {
    validateInteropConfig();
    return 0;
}
