#include "cpp_interface_advanced.h"
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <chrono>
#include <vector>
#include <map>
#include <string>

// Validación de extensión de archivo
bool validateFileExtension(const std::string& filePath, const std::string& extension) {
    return filePath.size() >= extension.size() &&
           filePath.compare(filePath.size() - extension.size(), extension.size(), extension) == 0;
}

// Creación de un nuevo entorno C++
bool CREATE_CPP_ENVIRONMENT(const std::string& id, const std::string& compiler_path) {
    if (cpp_environments.find(id) != cpp_environments.end()) {
        throw std::runtime_error("Error: El entorno con ID " + id + " ya existe");
    }
    if (!std::filesystem::exists(compiler_path)) {
        throw std::runtime_error("Error: Ruta del compilador no válida: " + compiler_path);
    }
    CppEnvironment new_env = {id, compiler_path, false, {}, 0};
    cpp_environments[id] = new_env;
    LOG_OPERATION("CREATE_CPP_ENVIRONMENT", {{"id", id}, {"compiler_path", compiler_path}}, true);
    return true;
}

// Inicialización del entorno C++
bool INITIALIZE_CPP_ENVIRONMENT(const std::string& id) {
    auto it = cpp_environments.find(id);
    if (it == cpp_environments.end()) {
        throw std::runtime_error("Error: Entorno con ID " + id + " no encontrado");
    }
    CppEnvironment& env = it->second;
    if (env.initialized) {
        return true;
    }
    env.initialized = CPP_INIT(env.compiler_path);
    env.last_execution_timestamp = TIMESTAMP();
    LOG_OPERATION("INITIALIZE_CPP_ENVIRONMENT", {{"id", id}}, env.initialized);
    return env.initialized;
}

// Unificación de evaluación y ejecución de archivos
bool EXECUTE_CPP_FILE(const std::string& id, const std::string& source_file_path, const std::string& output_file_path) {
    auto it = cpp_environments.find(id);
    if (it == cpp_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de C++ no inicializado o no encontrado");
    }
    if (!validateFileExtension(source_file_path, ".cpp")) {
        throw std::invalid_argument("Error: Archivo fuente debe tener extensión .cpp");
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    bool compile_success = CPP_COMPILE_FILE(it->second.compiler_path, source_file_path, output_file_path);
    if (!compile_success) {
        LOG_OPERATION("EXECUTE_CPP_FILE", {{"id", id}, {"source_file_path", source_file_path}}, false);
        return false;
    }

    bool execute_success = CPP_EXECUTE_FILE(output_file_path);
    it->second.last_execution_timestamp = TIMESTAMP();

    auto end_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double>(end_time - start_time).count();
    LOG_OPERATION("EXECUTE_CPP_FILE", {{"id", id}, {"source_file_path", source_file_path}, {"elapsed_time", std::to_string(elapsed_time)}}, execute_success);
    return execute_success;
}

// Paso de datos de MC++ a C++
bool PASS_DATA_TO_CPP(const std::string& id, const std::vector<std::string>& args) {
    auto it = cpp_environments.find(id);
    if (it == cpp_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de C++ no inicializado o no encontrado");
    }
    std::string formatted_args = JOIN(args, " ");
    bool success = CPP_SET_ARGS(it->second.compiler_path, formatted_args);
    LOG_OPERATION("PASS_DATA_TO_CPP", {{"id", id}, {"args", formatted_args}}, success);
    return success;
}

// Recuperación de datos de salida de C++
std::string RETRIEVE_OUTPUT_FROM_CPP(const std::string& id, const std::string& output_file_path) {
    auto it = cpp_environments.find(id);
    if (it == cpp_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de C++ no inicializado o no encontrado");
    }
    std::string output_data = CPP_GET_OUTPUT(output_file_path);
    LOG_OPERATION("RETRIEVE_OUTPUT_FROM_CPP", {{"id", id}, {"output_file_path", output_file_path}}, output_data);
    return output_data;
}

// Evaluación de código dinámico
bool EVALUATE_CPP_CODE(const std::string& id, const std::string& code) {
    auto it = cpp_environments.find(id);
    if (it == cpp_environments.end() || !it->second.initialized) {
        throw std::runtime_error("Error: Entorno de C++ no inicializado o no encontrado");
    }
    CppEnvironment& env = it->second;
    bool compile_success = CPP_COMPILE_CODE(env.compiler_path, code);
    env.last_execution_timestamp = TIMESTAMP();
    LOG_OPERATION("EVALUATE_CPP_CODE", {{"id", id}, {"code", code}}, compile_success);
    return compile_success;
}

// Cierre del entorno C++
bool CLOSE_CPP_ENVIRONMENT(const std::string& id) {
    auto it = cpp_environments.find(id);
    if (it == cpp_environments.end()) {
        throw std::runtime_error("Error: Entorno de C++ no encontrado");
    }
    bool close_success = CPP_SHUTDOWN(it->second.compiler_path);
    if (close_success) {
        cpp_environments.erase(it);
    }
    LOG_OPERATION("CLOSE_CPP_ENVIRONMENT", {{"id", id}}, close_success);
    return close_success;
}

// Listado de entornos activos
std::vector<std::map<std::string, std::string>> LIST_ACTIVE_CPP_ENVIRONMENTS() {
    std::vector<std::map<std::string, std::string>> active_envs;
    for (const auto& [id, env] : cpp_environments) {
        if (env.initialized) {
            active_envs.push_back({
                {"id", id},
                {"compiler_path", env.compiler_path},
                {"last_execution", std::to_string(env.last_execution_timestamp)}
            });
        }
    }
    LOG_OPERATION("LIST_ACTIVE_CPP_ENVIRONMENTS", {}, active_envs.size());
    return active_envs;
}
