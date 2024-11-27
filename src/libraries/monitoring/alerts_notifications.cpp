#include "alerts_notifications.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>

// Constructor
AlertsNotifications::AlertsNotifications() {
    notificationChannels = {
        {"email", "admin@company.com"},
        {"sms", "+1234567890"},
        {"webhook", "https://example.com/webhook"}
    };
    severityLevels = {"INFO", "WARNING", "CRITICAL"};
    alertPolicy = {
        {"retry_attempts", 3},
        {"retry_interval", 300},
        {"cooldown_period", 600}
    };
}

// Crear una nueva alerta y enviar notificación
bool AlertsNotifications::createAlert(const std::string& type, const std::string& severity, const std::string& message,
                                      const std::map<std::string, std::string>& details) {
    std::lock_guard<std::mutex> lock(alertMutex);
    if (std::find(severityLevels.begin(), severityLevels.end(), severity) == severityLevels.end()) {
        std::cerr << "Error: Nivel de severidad no válido\n";
        return false;
    }
    Alert alert = {std::to_string(activeAlerts.size() + 1), std::time(nullptr), type, severity, message, details, false};
    activeAlerts.push_back(alert);
    std::thread(&AlertsNotifications::sendNotification, this, alert).detach();
    logOperation("CREATE_ALERT", {{"type", type}, {"severity", severity}, {"message", message}});
    return true;
}

// Enviar notificación a los canales configurados
void AlertsNotifications::sendNotification(const Alert& alert) {
    std::lock_guard<std::mutex> lock(notificationMutex);
    for (const auto& channel : notificationChannels) {
        if (channel.first == "email") {
            std::cout << "Enviando correo a " << channel.second << ": " << alert.message << "\n";
        } else if (channel.first == "sms") {
            std::cout << "Enviando SMS a " << channel.second << ": " << alert.message << "\n";
        } else if (channel.first == "webhook") {
            std::cout << "Llamando webhook en " << channel.second << " con datos de alerta.\n";
        }
    }
    logOperation("SEND_NOTIFICATION", {{"id", alert.id}, {"severity", alert.severity}});
}

// Reconocer una alerta existente
bool AlertsNotifications::acknowledgeAlert(const std::string& alert_id) {
    std::lock_guard<std::mutex> lock(alertMutex);
    for (auto& alert : activeAlerts) {
        if (alert.id == alert_id) {
            alert.acknowledged = true;
            logOperation("ACKNOWLEDGE_ALERT", {{"id", alert_id}});
            return true;
        }
    }
    logOperation("ACKNOWLEDGE_ALERT_FAILED", {{"id", alert_id}});
    return false;
}

// Reintentar notificaciones para alertas no reconocidas
void AlertsNotifications::retryUnacknowledgedAlerts() {
    std::lock_guard<std::mutex> lock(alertMutex);
    for (auto& alert : activeAlerts) {
        if (!alert.acknowledged && alert.severity == "CRITICAL") {
            int retries = 0;
            while (retries < alertPolicy["retry_attempts"] && !alert.acknowledged) {
                sendNotification(alert);
                retries++;
                std::this_thread::sleep_for(std::chrono::seconds(alertPolicy["retry_interval"]));
            }
            logOperation("RETRY_UNACKNOWLEDGED_ALERT", {{"id", alert.id}, {"retries", std::to_string(retries)}});
        }
    }
}

// Limpieza de alertas viejas o reconocidas
int AlertsNotifications::cleanupOldAlerts() {
    std::lock_guard<std::mutex> lock(alertMutex);
    time_t currentTime = std::time(nullptr);
    auto initialCount = activeAlerts.size();
    activeAlerts.erase(std::remove_if(activeAlerts.begin(), activeAlerts.end(),
        [this, currentTime](const Alert& alert) {
            return alert.acknowledged || (currentTime - alert.timestamp > alertPolicy["cooldown_period"]);
        }), activeAlerts.end());
    int removedCount = initialCount - activeAlerts.size();
    logOperation("CLEANUP_OLD_ALERTS", {{"removed_count", std::to_string(removedCount)}});
    return removedCount;
}

// Generar reporte de alertas agrupado por tipo y severidad
std::map<std::string, std::map<std::string, int>> AlertsNotifications::generateAlertReport() const {
    std::lock_guard<std::mutex> lock(alertMutex);
    std::map<std::string, std::map<std::string, int>> report;
    for (const auto& level : severityLevels) {
        report[level] = {};
        for (const auto& alert : activeAlerts) {
            if (alert.severity == level) {
                report[level][alert.type]++;
            }
        }
    }
    logOperation("GENERATE_ALERT_REPORT", {});
    return report;
}

// Configurar un canal de notificación específico
bool AlertsNotifications::configureNotificationChannel(const std::string& channel, const std::string& destination) {
    std::lock_guard<std::mutex> lock(notificationMutex);
    if (notificationChannels.find(channel) == notificationChannels.end()) {
        std::cerr << "Error: Canal de notificación no válido\n";
        return false;
    }
    notificationChannels[channel] = destination;
    logOperation("CONFIGURE_NOTIFICATION_CHANNEL", {{"channel", channel}, {"destination", destination}});
    return true;
}

// Buscar alertas según contenido en mensaje o detalles
std::vector<Alert> AlertsNotifications::searchAlerts(const std::string& query) const {
    std::lock_guard<std::mutex> lock(alertMutex);
    std::vector<Alert> results;
    for (const auto& alert : activeAlerts) {
        if (alert.message.find(query) != std::string::npos) {
            results.push_back(alert);
        }
    }
    logOperation("SEARCH_ALERTS", {{"query", query}});
    return results;
}

// Análisis de frecuencia de alertas dentro de una ventana de tiempo
std::map<std::string, int> AlertsNotifications::alertFrequencyAnalysis(int window) const {
    std::lock_guard<std::mutex> lock(alertMutex);
    std::map<std::string, int> frequencyMap;
    time_t currentTime = std::time(nullptr);
    for (const auto& alert : activeAlerts) {
        if (currentTime - alert.timestamp <= window) {
            frequencyMap[alert.severity]++;
        }
    }
    logOperation("ALERT_FREQUENCY_ANALYSIS", {{"window", std::to_string(window)}});
    return frequencyMap;
}

// Activar escalada automática para alertas críticas no reconocidas
void AlertsNotifications::automaticEscalation() {
    std::lock_guard<std::mutex> lock(alertMutex);
    for (const auto& alert : activeAlerts) {
        if (alert.severity == "CRITICAL" && !alert.acknowledged) {
            sendNotification(alert);
            logOperation("AUTOMATIC_ESCALATION", {{"id", alert.id}});
        }
    }
}

// Función para registrar operaciones internas del sistema de alertas
void AlertsNotifications::logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const {
    std::cout << "Log Operation: " << operation << "\n";
    for (const auto& detail : details) {
        std::cout << detail.first << ": " << detail.second << "\n";
    }
}
