#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <unordered_map>
#include <mutex>

namespace mc_config {

    // Enumeración de tipos de configuración soportados
    enum class ConfigType { STRING, INTEGER, FLOAT, BOOLEAN };

    // Estructura para almacenar el tipo y el valor de configuración
    struct ConfigParam {
        ConfigType type;
        std::string value;

        ConfigParam(ConfigType t, const std::string& v) : type(t), value(v) {}
    };

    class ConfigManager {
    public:
        // Carga el archivo de configuración desde una ruta especificada
        static void loadConfigFile(const std::string& file_path);

        // Getters para distintos tipos de configuraciones
        static std::string getString(const std::string& key);
        static int getInt(const std::string& key);
        static float getFloat(const std::string& key);
        static bool getBool(const std::string& key);

        // Configuración de un parámetro en tiempo de ejecución
        static void setParam(const std::string& key, const std::string& value, ConfigType type);

        // Verifica si un parámetro existe en la configuración
        static bool hasParam(const std::string& key);

    private:
        // Mapa de parámetros de configuración y mutex para seguridad en concurrencia
        static std::unordered_map<std::string, ConfigParam> config_map;
        static std::mutex config_mutex;

        // Validación de la existencia y tipo de un parámetro
        static void validateParam(const std::string& key, ConfigType expected_type);
    };

} // namespace mc_config

#endif // CONFIG_MANAGER_H
