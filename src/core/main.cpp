#include "interpreter.h"
#include "compiler.h"
#include "config.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    // Inicialización de configuración global
    Config::initialize();
    
    try {
        if (argc > 1) {
            std::string mode = argv[1];
            if (mode == "interpret") {
                Interpreter interpreter;
                interpreter.run();
            } else if (mode == "compile") {
                Compiler compiler;
                compiler.run();
            } else {
                std::cerr << "Error: Modo desconocido: " << mode << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Uso: mc++ [interpret|compile]" << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
