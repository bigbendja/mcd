#ifndef MC_UTILS_CONFIG_H
#define MC_UTILS_CONFIG_H

#include <string>
#include <unordered_map>
#include <mutex>

namespace mc_utils {

    // Definición de tipos de configuración para estandarizar opciones de configuración
    enum class ConfigType {
        STRING,
        INTEGER,
        FLOAT,
        BOOLEAN
    };

    // Estructura para representar un parámetro de configuración con su tipo y valor
    struct ConfigParam {
        ConfigType type;
        std::string value;

        ConfigParam(ConfigType t, const std::string& v) : type(t), value(v) {}
    };

    class Config {
    public:
        // Inicialización de configuración desde un archivo JSON o similar
        static void loadConfigFile(const std::string& file_path);
        
        // Acceso a parámetros de configuración individuales con chequeo de tipo
        static std::string getString(const std::string& key);
        static int getInt(const std::string& key);
        static float getFloat(const std::string& key);
        static bool getBool(const std::string& key);

        // Funciones de configuración de parámetros dinámicos
        static void setParam(const std::string& key, const std::string& value, ConfigType type);
        static bool hasParam(const std::string& key);

    private:
        static std::unordered_map<std::string, ConfigParam> config_map;
        static std::mutex config_mutex;

        // Validación y conversión interna de valores
        static void validateParam(const std::string& key, ConfigType expected_type);
    };

} // namespace mc_utils

#endif // MC_UTILS_CONFIG_H
