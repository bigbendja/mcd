#include <iostream>
#include <fstream>
#include <stdexcept>
#include <json/json.h>
#include <filesystem>

bool validateIoConfig(const std::string& configPath) {
    if (!std::filesystem::exists(configPath)) {
        throw std::runtime_error("Error: Archivo de configuración no encontrado en " + configPath);
    }

    std::ifstream configFile(configPath);
    Json::Value config;
    configFile >> config;

    // Validar estructura principal
    if (!config.isMember("file_management") || !config.isMember("user_input") ||
        !config.isMember("output_formatting") || !config.isMember("logging")) {
        throw std::runtime_error("Error: Claves principales faltantes en el archivo de configuración");
    }

    // Validación del módulo `file_management`
    auto& fileManagement = config["file_management"];
    if (!fileManagement.isMember("default_directory") || !fileManagement.isMember("allowed_extensions") ||
        !fileManagement.isMember("max_file_size_mb")) {
        throw std::runtime_error("Error: Configuración incompleta en `file_management`");
    }
    if (!std::filesystem::exists(fileManagement["default_directory"].asString())) {
        throw std::runtime_error("Error: Directorio predeterminado no existe: " + fileManagement["default_directory"].asString());
    }
    if (!fileManagement["allowed_extensions"].isArray()) {
        throw std::runtime_error("Error: `allowed_extensions` debe ser una lista");
    }

    // Validación del módulo `user_input`
    auto& userInput = config["user_input"];
    if (!userInput.isMember("max_input_length") || !userInput.isMember("required_fields")) {
        throw std::runtime_error("Error: Configuración incompleta en `user_input`");
    }

    // Validación del módulo `output_formatting`
    auto& outputFormatting = config["output_formatting"];
    if (!outputFormatting.isMember("default_format") || !outputFormatting.isMember("precision")) {
        throw std::runtime_error("Error: Configuración incompleta en `output_formatting`");
    }

    // Validación del módulo `logging`
    auto& logging = config["logging"];
    if (!logging.isMember("enable_logging") || !logging.isMember("log_directory")) {
        throw std::runtime_error("Error: Configuración incompleta en `logging`");
    }
    if (!std::filesystem::exists(logging["log_directory"].asString())) {
        throw std::runtime_error("Error: Directorio de logs no existe: " + logging["log_directory"].asString());
    }

    std::cout << "Configuración validada correctamente." << std::endl;
    return true;
}
