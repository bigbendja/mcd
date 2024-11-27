#include "config_manager.h"
#include <fstream>
#include <json/json.h> // Librería JSON para el parseo, asegúrate de tener la dependencia
#include <stdexcept>
#include <mutex>

namespace mc_config {

    // Inicialización de variables estáticas
    std::unordered_map<std::string, ConfigParam> ConfigManager::config_map;
    std::mutex ConfigManager::config_mutex;

    void ConfigManager::loadConfigFile(const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Error: No se pudo abrir el archivo de configuración: " + file_path);
        }

        Json::Value root;
        file >> root;

        std::lock_guard<std::mutex> lock(config_mutex);
        for (const auto& key : root.getMemberNames()) {
            const Json::Value& value = root[key];
            if (value.isString()) {
                config_map[key] = ConfigParam(ConfigType::STRING, value.asString());
            } else if (value.isInt()) {
                config_map[key] = ConfigParam(ConfigType::INTEGER, std::to_string(value.asInt()));
            } else if (value.isDouble()) {
                config_map[key] = ConfigParam(ConfigType::FLOAT, std::to_string(value.asDouble()));
            } else if (value.isBool()) {
                config_map[key] = ConfigParam(ConfigType::BOOLEAN, value.asBool() ? "true" : "false");
            } else {
                throw std::runtime_error("Error: Tipo de parámetro no soportado en configuración para clave: " + key);
            }
        }
    }

    std::string ConfigManager::getString(const std::string& key) {
        validateParam(key, ConfigType::STRING);
        return config_map[key].value;
    }

    int ConfigManager::getInt(const std::string& key) {
        validateParam(key, ConfigType::INTEGER);
        return std::stoi(config_map[key].value);
    }

    float ConfigManager::getFloat(const std::string& key) {
        validateParam(key, ConfigType::FLOAT);
        return std::stof(config_map[key].value);
    }

    bool ConfigManager::getBool(const std::string& key) {
        validateParam(key, ConfigType::BOOLEAN);
        return config_map[key].value == "true";
    }

    void ConfigManager::setParam(const std::string& key, const std::string& value, ConfigType type) {
        std::lock_guard<std::mutex> lock(config_mutex);
        config_map[key] = ConfigParam(type, value);
    }

    bool ConfigManager::hasParam(const std::string& key) {
        std::lock_guard<std::mutex> lock(config_mutex);
        return config_map.find(key) != config_map.end();
    }

    void ConfigManager::validateParam(const std::string& key, ConfigType expected_type) {
        if (config_map.find(key) == config_map.end()) {
            throw std::runtime_error("Error: Parámetro de configuración no encontrado: " + key);
        }
        if (config_map[key].type != expected_type) {
            throw std::runtime_error("Error: Tipo incorrecto para el parámetro de configuración: " + key);
        }
    }

} // namespace mc_config
