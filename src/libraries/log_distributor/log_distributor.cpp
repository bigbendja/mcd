#include "log_distributor.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <nlohmann/json.hpp>

LogDistributorConfig globalConfig;

bool InitializeLogDistributor(const std::string& config_file) {
    std::ifstream configStream(config_file);
    if (!configStream.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el archivo de configuración: " << config_file << std::endl;
        return false;
    }

    nlohmann::json configJson;
    configStream >> configJson;

    globalConfig.central_server_url = configJson.value("central_server_url", "http://localhost:8080");
    globalConfig.max_retry_attempts = configJson.value("max_retry_attempts", 3);
    globalConfig.retry_interval_seconds = configJson.value("retry_interval_seconds", 5);

    std::cout << "[INFO] Log Distributor inicializado correctamente." << std::endl;
    return true;
}

bool SendLogToCentral(const std::string& node_id, const std::string& log_data) {
    int retry_count = 0;
    while (retry_count < globalConfig.max_retry_attempts) {
        // Simula un envío al servidor central
        std::cout << "[INFO] Enviando log al servidor central desde nodo: " << node_id << std::endl;
        std::cout << log_data << std::endl;

        // Simular éxito en el envío
        return true;

        retry_count++;
        std::this_thread::sleep_for(std::chrono::seconds(globalConfig.retry_interval_seconds));
    }

    std::cerr << "[ERROR] Fallo en el envío del log después de " << globalConfig.max_retry_attempts << " intentos." << std::endl;
    return false;
}

std::vector<std::string> QueryCentralLogs(const std::map<std::string, std::string>& filters) {
    std::cout << "[INFO] Consultando logs del servidor central con filtros:" << std::endl;
    for (const auto& [key, value] : filters) {
        std::cout << key << ": " << value << std::endl;
    }

    // Retorna una simulación de resultados
    return {"[INFO] Ejemplo de log 1", "[CRITICAL] Ejemplo de log 2"};
}
