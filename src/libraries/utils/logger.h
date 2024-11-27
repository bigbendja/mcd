#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <memory>
#include <chrono>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include "audit_manager.h"

namespace mc_common {

    // Niveles de log definidos en un espacio de nombres común para facilitar su uso en otros módulos
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR,
        DEBUG,
        CRITICAL
    };

} // namespace mc_common

namespace mc_utils {

    class Logger {
    public:
        // Configura el logger con el archivo de salida y el nivel de logging
        static void initialize(const std::string& file_path, mc_common::LogLevel level = mc_common::LogLevel::INFO);

        // Funciones de logging para cada nivel de prioridad
        static void log(mc_common::LogLevel level, const std::string& message);
        static void info(const std::string& message);
        static void warning(const std::string& message);
        static void error(const std::string& message);
        static void debug(const std::string& message);
        static void critical(const std::string& message);

        // Cierra el archivo de log
        static void finalize();

        // Configura un formato personalizado para los logs (por ejemplo, JSON)
        static void setLogFormat(const std::string& format);

        // Agrega un destino adicional para los logs (archivo remoto, base de datos, etc.)
        static void addLogDestination(const std::string& destinationType, const std::string& config);

    private:
        static std::ofstream log_file;         // Archivo de salida
        static mc_common::LogLevel log_level;  // Nivel de logging actual
        static std::mutex log_mutex;          // Mutex para sincronización
        static std::string log_format;        // Formato del log (por defecto, texto plano)
        static std::map<std::string, std::string> log_destinations; // Destinos adicionales

        // Constructor privado para evitar instancias
        Logger() = default;

        // Función interna para convertir el nivel de log en texto
        static std::string levelToString(mc_common::LogLevel level);

        // Función interna para obtener el tiempo actual formateado
        static std::string getCurrentTime();

        // Validación de configuración del nivel de log
        static bool isValidLogLevel(mc_common::LogLevel level);

        // Función interna para aplicar el formato al log
        static std::string formatLog(mc_common::LogLevel level, const std::string& message);
    };

} // namespace mc_utils

#endif // LOGGER_H
