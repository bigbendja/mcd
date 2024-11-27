#include "python_interface_advanced.h"
#include <iostream>
#include <stdexcept>
#include <chrono> // Para medir tiempos de ejecución

// Creación de un nuevo entorno Python
bool CREATE_PYTHON_ENVIRONMENT(const std::string& id, const std::string& interpreter_path) {
    if (python_environments.find(id) != python_environments.end()) {
        throw std::runtime_error("Error: El entorno con ID " + id + " ya existe");
    }
    if (!std::filesystem::exists(interpreter_path)) {
        throw std::invalid_argument("Error: Ruta del intérprete de Python no válida: " + interpreter_path);
    }
    PythonEnvironment new_env = {id, interpreter_path, false, {}, 0};
    python_environments[id] = new_env;
    LOG_OPERATION("CREATE_PYTHON_ENVIRONMENT", {{"id", id}, {"interpreter_path", interpreter_path}}, true);
    return true;
}

// Inicialización del entorno Python
bool INITIALIZE_PYTHON_ENVIRONMENT(const std::string& id) {
    auto it = python_environments.find(id);
    if (it == python_environments.end()) {
        throw std::runtime_error("Error: Entorno con ID " + id + " no encontrado");
    }
    PythonEnvironment& env = it->second;
    if (env.initialized) {
        return true; // Ya está inicializado
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    env.initialized = PYTHON_INIT(env.interpreter_path);
    env.last_execution_timestamp = TIMESTAMP();
    auto elapsed_time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
    
    LOG_OPERATION("INITIALIZE_PYTHON_ENVIRONMENT", {{"id", id}, {"elapsed_time", std::to_string(elapsed_time)}}, env.initialized);
    return env.initialized;
}

// Cargar un módulo en el entorno Python
bool LOAD_PYTHON_MODULE(const std::string& id, const std::string& module_name) {
    auto it = python_environments.find(id);
    if (it == python_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de Python no inicializado o no encontrado");
    }
    PythonEnvironment& env = it->second;
    bool load_success = PYTHON_IMPORT_MODULE(env.interpreter_path, module_name);
    if (load_success) {
        env.modules_loaded.push_back(module_name);
    }
    LOG_OPERATION("LOAD_PYTHON_MODULE", {{"id", id}, {"module_name", module_name}}, load_success);
    return load_success;
}

// Ejecución de una función en Python
Variant EXECUTE_PYTHON_FUNCTION(const std::string& id, const std::string& module_name, const std::string& function_name, const VariantList& args, const VariantMap& kwargs) {
    auto it = python_environments.find(id);
    if (it == python_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de Python no inicializado o no encontrado");
    }
    PythonEnvironment& env = it->second;

    auto start_time = std::chrono::high_resolution_clock::now();
    Variant result = PYTHON_CALL_FUNCTION(env.interpreter_path, module_name, function_name, args, kwargs);
    auto elapsed_time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
    
    env.last_execution_timestamp = TIMESTAMP();
    LOG_OPERATION("EXECUTE_PYTHON_FUNCTION", 
                  {{"id", id}, {"module_name", module_name}, {"function_name", function_name}, {"elapsed_time", std::to_string(elapsed_time)}}, 
                  result);
    return result;
}

// Paso de datos desde MC++ a Python
bool PASS_DATA_TO_PYTHON(const std::string& id, const Variant& data) {
    auto it = python_environments.find(id);
    if (it == python_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de Python no inicializado o no encontrado");
    }
    std::string json_data = TO_JSON(data);
    bool pass_success = PYTHON_SET_GLOBAL(it->second.interpreter_path, "mc_data", json_data);
    LOG_OPERATION("PASS_DATA_TO_PYTHON", {{"id", id}, {"data", json_data}}, pass_success);
    return pass_success;
}

// Recuperación de datos desde Python a MC++
Variant RETRIEVE_DATA_FROM_PYTHON(const std::string& id, const std::string& variable_name) {
    auto it = python_environments.find(id);
    if (it == python_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de Python no inicializado o no encontrado");
    }
    std::string json_data = PYTHON_GET_GLOBAL(it->second.interpreter_path, variable_name);
    Variant data = FROM_JSON(json_data);
    LOG_OPERATION("RETRIEVE_DATA_FROM_PYTHON", {{"id", id}, {"variable_name", variable_name}}, data);
    return data;
}

// Evaluación de código Python dinámico
Variant EVALUATE_PYTHON_CODE(const std::string& id, const std::string& code) {
    auto it = python_environments.find(id);
    if (it == python_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de Python no inicializado o no encontrado");
    }
    PythonEnvironment& env = it->second;

    auto start_time = std::chrono::high_resolution_clock::now();
    Variant result = PYTHON_EXECUTE_CODE(env.interpreter_path, code);
    auto elapsed_time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();

    env.last_execution_timestamp = TIMESTAMP();
    LOG_OPERATION("EVALUATE_PYTHON_CODE", {{"id", id}, {"code", code}, {"elapsed_time", std::to_string(elapsed_time)}}, result);
    return result;
}

// Cierre del entorno Python
bool CLOSE_PYTHON_ENVIRONMENT(const std::string& id) {
    auto it = python_environments.find(id);
    if (it == python_environments.end()) {
        throw std::runtime_error("Error: Entorno de Python no encontrado");
    }
    bool close_success = PYTHON_SHUTDOWN(it->second.interpreter_path);
    if (close_success) {
        python_environments.erase(it);
    }
    LOG_OPERATION("CLOSE_PYTHON_ENVIRONMENT", {{"id", id}}, close_success);
    return close_success;
}

// Listado de entornos Python activos
std::vector<VariantMap> LIST_ACTIVE_ENVIRONMENTS() {
    std::vector<VariantMap> active_envs;
    for (const auto& pair : python_environments) {
        const PythonEnvironment& env = pair.second;
        if (env.initialized) {
            active_envs.push_back({{"id", env.id}, {"modules_loaded", env.modules_loaded}, {"last_execution", std::to_string(env.last_execution_timestamp)}});
        }
    }
    LOG_OPERATION("LIST_ACTIVE_ENVIRONMENTS", {}, static_cast<int>(active_envs.size()));
    return active_envs;
}

// Verificación de integridad del entorno Python
bool VERIFY_ENVIRONMENT_INTEGRITY(const std::string& id) {
    auto it = python_environments.find(id);
    if (it == python_environments.end()) {
        throw std::runtime_error("Error: Entorno de Python no encontrado");
    }
    bool integrity_check = PYTHON_VERIFY_INTEGRITY(it->second.interpreter_path);
    LOG_OPERATION("VERIFY_ENVIRONMENT_INTEGRITY", {{"id", id}}, integrity_check);
    return integrity_check;
}

// Configuración de parámetros del entorno Python
bool SET_PYTHON_CONFIG(const std::string& id, const std::string& config_key, const Variant& config_value) {
    auto it = python_environments.find(id);
    if (it == python_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de Python no inicializado o no encontrado");
    }
    bool config_success = PYTHON_SET_CONFIG(it->second.interpreter_path, config_key, config_value);
    LOG_OPERATION("SET_PYTHON_CONFIG", {{"id", id}, {"config_key", config_key}, {"config_value", config_value}}, config_success);
    return config_success;
}
