#include "monitoring.h"

// Constructor que configura y prepara la instancia de Monitoring
Monitoring::Monitoring() {
    configureMonitoringSettings();
    initializePerformanceMonitoring();
    initializeLoggingAudit();
    initializeAlertsNotifications();
}

// Funciones de inicialización de los módulos

void Monitoring::initializePerformanceMonitoring() {
    performanceMonitoring = PerformanceMonitoring();
    // Configuración específica de umbrales
    performanceMonitoring.setThresholds({
        {"cpu", 0.85},
        {"memory", 0.80},
        {"disk", 0.75},
        {"network", 0.70}
    });
}

void Monitoring::initializeLoggingAudit() {
    loggingAudit = LoggingAudit();
    // Configuración del nivel de logs y política de retención
    loggingAudit.setLogLevel("INFO");
    loggingAudit.configureRetentionPolicy(10000, 30 * 24 * 60 * 60); // 30 días
}

void Monitoring::initializeAlertsNotifications() {
    alertsNotifications = AlertsNotifications();
    // Configuración de canales de notificación
    alertsNotifications.configureNotificationChannel("email", "alerts@company.com");
    alertsNotifications.configureNotificationChannel("sms", "+1234567890");
    alertsNotifications.configureNotificationChannel("webhook", "https://example.com/webhook");
}

// Funciones de monitoreo delegadas a los módulos

bool Monitoring::monitorAndScaleCPU(float threshold) {
    return performanceMonitoring.monitorAndScaleCPU(threshold);
}

std::map<std::string, float> Monitoring::monitorMemoryUsage(float threshold, bool optimize) {
    return performanceMonitoring.monitorMemoryUsage(threshold, optimize);
}

bool Monitoring::monitorNetworkTraffic(float maxBandwidth) {
    return performanceMonitoring.monitorNetworkTraffic(maxBandwidth);
}

// Función para registrar eventos prioritarios
bool Monitoring::logPriorityEvent(const std::string& eventType, const std::string& description, const std::string& priority) {
    return loggingAudit.logPriorityEvent(eventType, description, priority);
}

// Función para crear alertas
bool Monitoring::createAlert(const std::string& type, const std::string& severity, const std::string& message) {
    return alertsNotifications.createAlert(type, severity, message);
}

// Generación de reportes y auditoría

std::map<std::string, std::map<std::string, int>> Monitoring::generateAlertReport() {
    return alertsNotifications.generateAlertReport();
}

std::map<std::string, int> Monitoring::eventFrequencyAnalysis(int window) {
    return loggingAudit.eventFrequencyAnalysis(window);
}

// Limpieza y aplicación de políticas de retención

int Monitoring::enforceRetentionPolicy() {
    int logsRemoved = loggingAudit.enforceRetentionPolicy();
    int alertsRemoved = alertsNotifications.cleanupOldAlerts();
    loggingAudit.addLog("INFO", "RetentionPolicy", "Retention policy enforced", {
        {"logs_removed", std::to_string(logsRemoved)},
        {"alerts_removed", std::to_string(alertsRemoved)}
    });
    return logsRemoved + alertsRemoved;
}

int Monitoring::cleanupOldAlerts() {
    int removed = alertsNotifications.cleanupOldAlerts();
    loggingAudit.addLog("INFO", "AlertCleanup", "Old alerts cleaned up", {
        {"alerts_removed", std::to_string(removed)}
    });
    return removed;
}

// Configuración interna del sistema de monitoreo
void Monitoring::configureMonitoringSettings() {
    // Configuración centralizada para umbrales y políticas
    performanceMonitoring.setThresholds({
        {"cpu", 0.85},
        {"memory", 0.80},
        {"disk", 0.75},
        {"network", 0.70}
    });
    loggingAudit.setLogLevel("INFO");
    alertsNotifications.configureNotificationChannel("email", "alerts@company.com");
    alertsNotifications.configureNotificationChannel("sms", "+1234567890");
    alertsNotifications.configureNotificationChannel("webhook", "https://example.com/webhook");
}

// Exportación de reportes

std::string Monitoring::exportMonitoringReport() {
    auto performanceReport = performanceMonitoring.generatePerformanceReport();
    auto alertReport = alertsNotifications.generateAlertReport();
    auto logReport = loggingAudit.generateLogReport();

    // Combina los datos en un formato JSON (simulado)
    std::ostringstream reportStream;
    reportStream << "{\n"
                 << "  \"performance\": " << performanceReport.toJSON() << ",\n"
                 << "  \"alerts\": " << alertReport.toJSON() << ",\n"
                 << "  \"logs\": " << logReport.toJSON() << "\n"
                 << "}";
    loggingAudit.addLog("INFO", "ExportReport", "Monitoring report exported");
    return reportStream.str();
}
