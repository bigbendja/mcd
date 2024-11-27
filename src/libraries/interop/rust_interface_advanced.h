#ifndef RUST_INTERFACE_ADVANCED_H
#define RUST_INTERFACE_ADVANCED_H

#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <unordered_map>

/**
 * @brief Estructura que representa un entorno embebido de Rust y su configuración.
 */
struct RustEnvironment {
    std::string id;                          // Identificador único del entorno Rust.
    std::string library_path;                 // Ruta a la biblioteca de Rust.
    bool initialized;                         // Indica si el entorno ha sido inicializado.
    std::vector<std::string> loaded_functions; // Lista de funciones cargadas en el entorno.
    std::time_t last_execution_timestamp;     // Timestamp de la última ejecución en el entorno.

    RustEnvironment(const std::string& id, const std::string& library_path);
};

/**
 * @brief Clase RustInterfaceAdvanced: Gestiona la integración avanzada con entornos embebidos de Rust.
 */
class RustInterfaceAdvanced {
public:
    // Inicialización y gestión de entornos Rust embebidos
    bool initializeRustEnvironment(const std::string& id, const std::string& library_path);
    bool loadRustFunction(const std::string& id, const std::string& function_name);
    std::string executeRustFunction(const std::string& id, const std::string& function_name, const std::vector<std::string>& args);
    bool passDataToRust(const std::string& id, const std::string& json_data);
    std::string retrieveDataFromRust(const std::string& id, const std::string& variable_name);
    bool closeRustEnvironment(const std::string& id);
    std::vector<std::map<std::string, std::string>> listActiveRustEnvironments() const;
    bool verifyRustEnvironmentIntegrity(const std::string& id);
    bool setRustConfig(const std::string& id, const std::string& config_key, const std::string& config_value);

private:
    // Almacena todos los entornos embebidos de Rust
    std::unordered_map<std::string, RustEnvironment> rust_environments;

    // Métodos auxiliares para verificar el estado del entorno y la existencia de funciones
    bool isEnvironmentInitialized(const std::string& id) const;
    bool functionExists(const std::string& id, const std::string& function_name) const;

    // Métodos auxiliares para registro de operaciones y gestión de strings
    void logOperation(const std::string& operation, const std::string& id, const std::map<std::string, std::string>& params, const std::string& result) const;
    std::string joinStrings(const std::vector<std::string>& elements, const std::string& delimiter) const;
};

// Funciones de interop con Rust (simulación)
bool rust_initialize_library(const std::string& library_path);
bool rust_load_function(const std::string& library_path, const std::string& function_name);
std::string rust_call_function(const std::string& library_path, const std::string& function_name, const std::vector<std::string>& args);
bool rust_set_global_data(const std::string& library_path, const std::string& json_data);
std::string rust_get_global_data(const std::string& library_path, const std::string& variable_name);
bool rust_shutdown_library(const std::string& library_path);
bool rust_verify_integrity(const std::string& library_path);
bool rust_set_config(const std::string& library_path, const std::string& config_key, const std::string& config_value);

#endif // RUST_INTERFACE_ADVANCED_H
