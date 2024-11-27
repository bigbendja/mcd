#ifndef CPP_INTERFACE_ADVANCED_H
#define CPP_INTERFACE_ADVANCED_H

#include <string>
#include <list>

/**
 * Módulo de Interfaz C++ Avanzado en MC++: Facilita la interoperabilidad y ejecución de código C++ embebido.
 */

class CppInterface {
public:
    // Funciones de gestión de entornos embebidos de C++
    static bool createEnvironment(const std::string& id, const std::string& compilerPath = "/usr/bin/g++");
    static bool initializeEnvironment(const std::string& id);
    static bool closeEnvironment(const std::string& id);

    // Funciones de carga y ejecución
    static bool loadLibrary(const std::string& id, const std::string& libraryPath);
    static bool compileAndExecuteFile(const std::string& id, const std::string& sourceFilePath, const std::string& outputFilePath);
    static bool evaluateCode(const std::string& id, const std::string& code);

    // Funciones de intercambio de datos
    static std::string passDataToCpp(const std::string& id, const std::list<std::string>& args);
    static std::string retrieveOutputFromCpp(const std::string& id, const std::string& outputFilePath);

    // Listado y verificación de entornos
    static std::list<std::string> listActiveEnvironments();
    static bool verifyEnvironmentIntegrity(const std::string& id);

    // Configuración dinámica de entorno
    static bool setConfig(const std::string& id, const std::string& configKey, const std::string& configValue);
};

#endif // CPP_INTERFACE_ADVANCED_H
