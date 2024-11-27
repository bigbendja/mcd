#include "audit_manager.h"
#include "encryption.h"      // Para cifrado de logs
#include "log_distributor.h" // Para integración con sistema central de logs
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <map>
#include <mutex>
#include <json/json.h>       // Para cargar configuraciones desde security_config.json

namespace mc_security {

    // Inicialización de variables estáticas
    std::vector<std::string> AuditManager::eventLog;
    std::mutex AuditManager::logMutex;
    std::string AuditManager::logFile = "";

    // Variables para configuración de cifrado
    std::string encryptionKey;
    std::string encryptionIV;

    // Cargar configuración desde security_config.json
    void AuditManager::loadConfig(const std::string& configFilePath) {
        std::ifstream configFile(configFilePath);
        if (!configFile.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo de configuración: " + configFilePath);
        }

        Json::Value config;
        configFile >> config;

        encryptionKey = config["audit"]["audit_trail_encryption"]["key"].asString();
        encryptionIV = config["audit"]["audit_trail_encryption"]["iv"].asString();

        if (encryptionKey.empty() || encryptionIV.empty()) {
            throw std::runtime_error("Claves de cifrado para auditoría no están configuradas correctamente.");
        }

        // Configurar el sistema central de logs desde configuración
        std::string centralNode = config["audit"]["central_node"].asString();
        if (!InitializeLogDistributor(centralNode)) {
            throw std::runtime_error("Error al inicializar el distribuidor de logs con el nodo central.");
        }
    }

    // Función auxiliar para obtener la representación de nivel como texto
    std::string AuditManager::getLevelString(EventLevel level) {
        switch (level) {
            case EventLevel::INFO: return "[INFO]";
            case EventLevel::WARNING: return "[WARNING]";
            case EventLevel::CRITICAL: return "[CRITICAL]";
        }
        return "[UNKNOWN]";
    }

    // Función auxiliar para obtener una marca de tiempo formateada
    std::string AuditManager::getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << "[" << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "]";
        return oss.str();
    }

    // Método para registrar eventos en el sistema de auditoría
    void AuditManager::logEvent(const std::string& event, EventLevel level) {
        std::lock_guard<std::mutex> lock(logMutex);

        std::string formattedEvent = getCurrentTimestamp() + " " + getLevelString(level) + " " + event;
        eventLog.push_back(formattedEvent);

        // Salida inmediata al log para visibilidad
        std::cout << formattedEvent << std::endl;

        // Escribir logs cifrados en archivo
        if (!logFile.empty()) {
            std::ofstream outFile(logFile, std::ios::app);
            if (outFile.is_open()) {
                try {
                    std::string encryptedEvent = AESEncrypt(formattedEvent, encryptionKey, encryptionIV);
                    outFile << encryptedEvent << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "[ERROR] Falló el cifrado del log: " << e.what() << std::endl;
                }
                outFile.close();
            } else {
                std::cerr << "[ERROR] No se pudo escribir en el archivo de log: " << logFile << std::endl;
            }
        }

        // Enviar log al sistema central
        if (!SendLogToCentral("Node1", formattedEvent)) {
            std::cerr << "[ERROR] No se pudo enviar el log al sistema central." << std::endl;
        }
    }

    // Método para analizar patrones en el registro de eventos
    void AuditManager::analyzePatterns() {
        std::lock_guard<std::mutex> lock(logMutex);

        std::map<std::string, int> failedLoginAttempts;

        for (const auto& event : eventLog) {
            if (event.find("Failed Login") != std::string::npos) {
                size_t userStart = event.find("User: ") + 6;
                size_t userEnd = event.find(" ", userStart);
                std::string username = event.substr(userStart, userEnd - userStart);
                failedLoginAttempts[username]++;
            }
        }

        for (const auto& [user, count] : failedLoginAttempts) {
            if (count > 3) { // Límite configurable en security_config.json
                logEvent("Alerta: Usuario " + user + " tiene múltiples intentos fallidos.", EventLevel::WARNING);
            }
        }
    }

    // Método para analizar patrones en logs distribuidos
    void AuditManager::analyzeDistributedPatterns(const std::vector<std::string>& nodes) {
        std::lock_guard<std::mutex> lock(logMutex);

        std::vector<std::string> distributedLogs;

        // Recuperar logs de todos los nodos especificados
        for (const auto& node : nodes) {
            auto logs = RetrieveLogsFromCentral(node);
            distributedLogs.insert(distributedLogs.end(), logs.begin(), logs.end());
        }

        // Análisis de patrones en los logs combinados
        std::map<std::string, int> failedLoginAttempts;

        for (const auto& event : distributedLogs) {
            if (event.find("Failed Login") != std::string::npos) {
                size_t userStart = event.find("User: ") + 6;
                size_t userEnd = event.find(" ", userStart);
                std::string username = event.substr(userStart, userEnd - userStart);
                failedLoginAttempts[username]++;
            }
        }

        // Generar alertas si se detectan múltiples intentos fallidos
        for (const auto& [user, count] : failedLoginAttempts) {
            if (count > 3) { // Límite configurable en security_config.json
                logEvent("Alerta distribuida: Usuario " + user + " tiene múltiples intentos fallidos en nodos distribuidos.",
                         EventLevel::WARNING);
            }
        }
    }

    // Método para recuperar una lista de eventos críticos
    std::vector<std::string> AuditManager::getCriticalEvents() {
        std::lock_guard<std::mutex> lock(logMutex);

        std::vector<std::string> criticalEvents;
        std::copy_if(eventLog.begin(), eventLog.end(), std::back_inserter(criticalEvents),
                     [](const std::string& event) {
                         return event.find("[CRITICAL]") != std::string::npos;
                     });

        return criticalEvents;
    }

    // Método para configurar un archivo de salida para logs
    void AuditManager::setLogFile(const std::string& filePath) {
        std::lock_guard<std::mutex> lock(logMutex);
        logFile = filePath;
        logEvent("Archivo de log configurado en: " + filePath, EventLevel::INFO);
    }

    // Método para revisar logs descifrados
    void AuditManager::viewAuditLogs() {
        std::lock_guard<std::mutex> lock(logMutex);

        std::ifstream inFile(logFile);
        if (inFile.is_open()) {
            std::string encryptedLog;
            while (getline(inFile, encryptedLog)) {
                try {
                    std::string decryptedLog = AESDecrypt(encryptedLog, encryptionKey, encryptionIV);
                    std::cout << decryptedLog << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "[ERROR] Falló el descifrado de un log: " << e.what() << std::endl;
                }
            }
            inFile.close();
        } else {
            std::cerr << "[ERROR] No se pudo abrir el archivo de log para lectura." << std::endl;
        }
    }
}
