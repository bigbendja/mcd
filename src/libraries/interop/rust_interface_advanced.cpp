#include "rust_interface_advanced.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>

// Constructor del entorno Rust embebido
RustEnvironment::RustEnvironment(const std::string& id, const std::string& library_path)
    : id(id), library_path(library_path), initialized(false), last_execution_timestamp(0) {}

// Inicializa el entorno de Rust embebido cargando la biblioteca
bool RustInterfaceAdvanced::initializeRustEnvironment(const std::string& id, const std::string& library_path) {
    if (rust_environments.find(id) != rust_environments.end()) {
        throw std::runtime_error("Error: El entorno Rust con ID " + id + " ya existe.");
    }
    if (library_path.empty()) {
        throw std::invalid_argument("Error: La ruta de la biblioteca no puede estar vacía.");
    }

    RustEnvironment new_env(id, library_path);
    new_env.initialized = rust_initialize_library(new_env.library_path);
    new_env.last_execution_timestamp = std::time(nullptr);

    if (!new_env.initialized) {
        throw std::runtime_error("Error: No se pudo inicializar el entorno Rust.");
    }

    rust_environments[id] = new_env;
    logOperation("INITIALIZE_RUST_ENVIRONMENT", id, {{"library_path", library_path}}, new_env.initialized);
    return true;
}

// Carga una función desde una biblioteca Rust en el entorno especificado
bool RustInterfaceAdvanced::loadRustFunction(const std::string& id, const std::string& function_name) {
    if (!isEnvironmentInitialized(id)) {
        throw std::runtime_error("Error: Entorno de Rust no inicializado o no encontrado.");
    }
    if (function_name.empty()) {
        throw std::invalid_argument("Error: El nombre de la función no puede estar vacío.");
    }

    RustEnvironment& env = rust_environments[id];
    bool load_success = rust_load_function(env.library_path, function_name);

    if (load_success) {
        env.loaded_functions.push_back(function_name);
    } else {
        logOperation("LOAD_RUST_FUNCTION_FAILED", id, {{"function_name", function_name}}, false);
    }

    logOperation("LOAD_RUST_FUNCTION", id, {{"function_name", function_name}}, load_success);
    return load_success;
}

// Ejecuta una función Rust con argumentos y retorna el resultado convertido a formato MC++
std::string RustInterfaceAdvanced::executeRustFunction(const std::string& id, const std::string& function_name, const std::vector<std::string>& args) {
    if (!isEnvironmentInitialized(id) || !functionExists(id, function_name)) {
        throw std::runtime_error("Error: Función de Rust no encontrada en el entorno.");
    }

    RustEnvironment& env = rust_environments[id];
    std::string result = rust_call_function(env.library_path, function_name, args);

    env.last_execution_timestamp = std::time(nullptr);
    logOperation("EXECUTE_RUST_FUNCTION", id, {{"function_name", function_name}, {"args", joinStrings(args, ",")}}, result);
    return result;
}

// Transfiere datos de MC++ a Rust en formato JSON
bool RustInterfaceAdvanced::passDataToRust(const std::string& id, const std::string& json_data) {
    if (!isEnvironmentInitialized(id)) {
        throw std::runtime_error("Error: Entorno de Rust no inicializado o no encontrado.");
    }
    if (json_data.empty()) {
        throw std::invalid_argument("Error: Los datos en JSON no pueden estar vacíos.");
    }

    RustEnvironment& env = rust_environments[id];
    bool success = rust_set_global_data(env.library_path, json_data);

    logOperation("PASS_DATA_TO_RUST", id, {{"json_data", json_data}}, success);
    return success;
}

// Recupera datos desde Rust en formato JSON y los convierte al formato nativo MC++
std::string RustInterfaceAdvanced::retrieveDataFromRust(const std::string& id, const std::string& variable_name) {
    if (!isEnvironmentInitialized(id)) {
        throw std::runtime_error("Error: Entorno de Rust no inicializado o no encontrado.");
    }
    if (variable_name.empty()) {
        throw std::invalid_argument("Error: El nombre de la variable no puede estar vacío.");
    }

    RustEnvironment& env = rust_environments[id];
    std::string json_data = rust_get_global_data(env.library_path, variable_name);

    logOperation("RETRIEVE_DATA_FROM_RUST", id, {{"variable_name", variable_name}}, json_data);
    return json_data;
}

// Cierra y limpia el entorno Rust embebido
bool RustInterfaceAdvanced::closeRustEnvironment(const std::string& id) {
    auto it = rust_environments.find(id);
    if (it == rust_environments.end()) {
        throw std::runtime_error("Error: Entorno de Rust no encontrado.");
    }

    RustEnvironment& env = it->second;
    bool success = rust_shutdown_library(env.library_path);

    if (success) {
        rust_environments.erase(it);
    }

    logOperation("CLOSE_RUST_ENVIRONMENT", id, {}, success);
    return success;
}

// Lista los entornos Rust activos y sus funciones cargadas
std::vector<std::map<std::string, std::string>> RustInterfaceAdvanced::listActiveRustEnvironments() const {
    std::vector<std::map<std::string, std::string>> active_envs;
    for (const auto& [id, env] : rust_environments) {
        if (env.initialized) {
            active_envs.push_back({
                {"id", env.id},
                {"library_path", env.library_path},
                {"loaded_functions", joinStrings(env.loaded_functions, ",")},
                {"last_execution_timestamp", std::to_string(env.last_execution_timestamp)}
            });
        }
    }
    logOperation("LIST_ACTIVE_RUST_ENVIRONMENTS", "", {}, active_envs.size());
    return active_envs;
}

// Verifica la integridad del entorno Rust embebido
bool RustInterfaceAdvanced::verifyRustEnvironmentIntegrity(const std::string& id) {
    if (!isEnvironmentInitialized(id)) {
        throw std::runtime_error("Error: Entorno de Rust no encontrado.");
    }

    RustEnvironment& env = rust_environments[id];
    bool integrity_check = rust_verify_integrity(env.library_path);

    logOperation("VERIFY_RUST_ENVIRONMENT_INTEGRITY", id, {}, integrity_check);
    return integrity_check;
}

// Ajusta la configuración del entorno Rust embebido
bool RustInterfaceAdvanced::setRustConfig(const std::string& id, const std::string& config_key, const std::string& config_value) {
    if (!isEnvironmentInitialized(id)) {
        throw std::runtime_error("Error: Entorno de Rust no inicializado o no encontrado.");
    }

    RustEnvironment& env = rust_environments[id];
    bool success = rust_set_config(env.library_path, config_key, config_value);

    logOperation("SET_RUST_CONFIG", id, {{"config_key", config_key}, {"config_value", config_value}}, success);
    return success;
}

// Helper para verificar si el entorno está inicializado
bool RustInterfaceAdvanced::isEnvironmentInitialized(const std::string& id) const {
    auto it = rust_environments.find(id);
    return it != rust_environments.end() && it->second.initialized;
}

// Helper para verificar si la función existe en el entorno
bool RustInterfaceAdvanced::functionExists(const std::string& id, const std::string& function_name) const {
    const auto& env = rust_environments.at(id);
    return std::find(env.loaded_functions.begin(), env.loaded_functions.end(), function_name) != env.loaded_functions.end();
}

// Helper para registrar operaciones de interop
void RustInterfaceAdvanced::logOperation(const std::string& operation, const std::string& id, const std::map<std::string, std::string>& params, const std::string& result) const {
    std::cout << "[LOG] Operation: " << operation << ", ID: " << id;
    for (const auto& [key, value] : params) {
        std::cout << ", " << key << ": " << value;
    }
    std::cout << ", Result: " << result << std::endl;
}

// Helper para unir strings
std::string RustInterfaceAdvanced::joinStrings(const std::vector<std::string>& elements, const std::string& delimiter) const {
    std::ostringstream os;
    for (size_t i = 0; i < elements.size(); ++i) {
        os << elements[i];
        if (i < elements.size() - 1) os << delimiter;
    }
    return os.str();
}
