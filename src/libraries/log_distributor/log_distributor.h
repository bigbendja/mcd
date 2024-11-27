#ifndef LOG_DISTRIBUTOR_H
#define LOG_DISTRIBUTOR_H

#include <string>
#include <map>
#include <vector>

// Configuración de la librería
struct LogDistributorConfig {
    std::string central_server_url;
    int max_retry_attempts;
    int retry_interval_seconds;
};

// Inicializa el sistema de distribución de logs
bool InitializeLogDistributor(const std::string& config_file);

// Envía un log al servidor central
bool SendLogToCentral(const std::string& node_id, const std::string& log_data);

// Consulta logs centralizados con filtros
std::vector<std::string> QueryCentralLogs(const std::map<std::string, std::string>& filters);

#endif // LOG_DISTRIBUTOR_H
