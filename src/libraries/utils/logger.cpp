#include "logger.h"

namespace mc_utils {

    // Inicialización de variables estáticas
    std::ofstream Logger::log_file;
    mc_common::LogLevel Logger::log_level = mc_common::LogLevel::INFO;
    std::mutex Logger::log_mutex;
    std::string Logger::log_format = "[%TIME%] [%LEVEL%] %MESSAGE%"; // Formato por defecto
    std::map<std::string, std::string> Logger::log_destinations;

    void Logger::initialize(const std::string& file_path, mc_common::LogLevel level) {
        std::lock_guard<std::mutex> lock(log_mutex);
        if (!isValidLogLevel(level)) {
            throw std::invalid_argument("Nivel de log no válido.");
        }
        log_level = level;
        log_file.open(file_path, std::ios::out | std::ios::app);
        if (!log_file.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo de log: " + file_path);
        }
    }

    void Logger::log(mc_common::LogLevel level, const std::string& message) {
        if (level < log_level) return;

        std::lock_guard<std::mutex> lock(log_mutex);
        std::string formatted_message = formatLog(level, message);

        // Escribir en el archivo de log principal
        if (log_file.is_open()) {
            log_file << formatted_message << std::endl;
        }

        // Enviar a destinos adicionales
        for (const auto& [type, config] : log_destinations) {
            if (type == "remote") {
                // Ejemplo: enviar el log a un servidor remoto
                // sendToRemoteServer(config, formatted_message);
            }
            else if (type == "database") {
                // Ejemplo: guardar el log en una base de datos
                // saveToDatabase(config, formatted_message);
            }
        }
    }

    void Logger::info(const std::string& message) {
        log(mc_common::LogLevel::INFO, message);
    }

    void Logger::warning(const std::string& message) {
        log(mc_common::LogLevel::WARNING, message);
    }

    void Logger::error(const std::string& message) {
        log(mc_common::LogLevel::ERROR, message);
    }

    void Logger::debug(const std::string& message) {
        log(mc_common::LogLevel::DEBUG, message);
    }

    void Logger::critical(const std::string& message) {
        log(mc_common::LogLevel::CRITICAL, message);
        // Registrar el evento crítico en el sistema de auditoría
        mc_security::AuditManager::logEvent(message, mc_security::AuditManager::EventLevel::CRITICAL);
    }

    void Logger::finalize() {
        std::lock_guard<std::mutex> lock(log_mutex);
        if (log_file.is_open()) {
            log_file.close();
        }
    }

    void Logger::setLogFormat(const std::string& format) {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_format = format;
    }

    void Logger::addLogDestination(const std::string& destinationType, const std::string& config) {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_destinations[destinationType] = config;
    }

    std::string Logger::levelToString(mc_common::LogLevel level) {
        switch (level) {
            case mc_common::LogLevel::INFO: return "INFO";
            case mc_common::LogLevel::WARNING: return "WARNING";
            case mc_common::LogLevel::ERROR: return "ERROR";
            case mc_common::LogLevel::DEBUG: return "DEBUG";
            case mc_common::LogLevel::CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
        }
    }

    std::string Logger::getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    bool Logger::isValidLogLevel(mc_common::LogLevel level) {
        return level == mc_common::LogLevel::INFO || level == mc_common::LogLevel::WARNING ||
               level == mc_common::LogLevel::ERROR || level == mc_common::LogLevel::DEBUG ||
               level == mc_common::LogLevel::CRITICAL;
    }

    std::string Logger::formatLog(mc_common::LogLevel level, const std::string& message) {
        std::string formatted = log_format;
        formatted.replace(formatted.find("%TIME%"), 6, getCurrentTime());
        formatted.replace(formatted.find("%LEVEL%"), 7, levelToString(level));
        formatted.replace(formatted.find("%MESSAGE%"), 9, message);
        return formatted;
    }

} // namespace mc_utils
