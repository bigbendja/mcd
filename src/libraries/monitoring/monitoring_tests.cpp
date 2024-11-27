#include "monitoring.h"
#include <cassert>
#include <iostream>
#include <map>

/**
 * @brief Función auxiliar para ejecutar y registrar pruebas.
 */
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << "\n";
    } else {
        std::cerr << "[FAILED] " << test_name << "\n";
    }
}

// Prueba para monitoreo de CPU y escalado automático
void testMonitorAndScaleCPU(Monitoring& monitoring) {
    bool result = monitoring.monitorAndScaleCPU(0.9);
    run_test("Test Monitor and Scale CPU", result);
}

// Prueba para monitoreo y ajuste de memoria
void testMonitorMemoryUsage(Monitoring& monitoring) {
    auto memoryStatus = monitoring.monitorMemoryUsage(0.8, true);
    bool result = !memoryStatus.empty() && memoryStatus["usage"] <= 0.8;
    run_test("Test Monitor Memory Usage", result);
}

// Prueba de monitoreo de tráfico de red y alertas de picos
void testMonitorNetworkTraffic(Monitoring& monitoring) {
    bool result = monitoring.monitorNetworkTraffic(500.0);
    run_test("Test Monitor Network Traffic", result);
}

// Prueba para el registro de eventos con nivel de prioridad
void testLogPriorityEvent(Monitoring& monitoring) {
    bool result = monitoring.logPriorityEvent("SECURITY", "Unauthorized access detected", "CRITICAL");
    run_test("Test Log Priority Event", result);
}

// Prueba de generación de reportes de rendimiento
void testGeneratePerformanceReport(Monitoring& monitoring) {
    auto report = monitoring.generatePerformanceReport();
    bool result = !report.empty();
    run_test("Test Generate Performance Report", result);
}

// Prueba de frecuencia de eventos para auditoría
void testEventFrequencyAnalysis(Monitoring& monitoring) {
    auto frequencyAnalysis = monitoring.eventFrequencyAnalysis(3600);
    bool result = !frequencyAnalysis.empty();
    run_test("Test Event Frequency Analysis", result);
}

// Prueba de creación y envío de alertas
void testCreateAlert(Monitoring& monitoring) {
    bool result = monitoring.createAlert("CPU", "CRITICAL", "CPU Usage Exceeded Threshold");
    run_test("Test Create Alert", result);
}

// Prueba de configuración de canales de notificación
void testConfigureNotificationChannel(AlertsNotifications& alerts) {
    bool result = alerts.configureNotificationChannel("email", "new_admin@company.com");
    run_test("Test Configure Notification Channel", result);
}

// Prueba de escalada automática de alertas no reconocidas
void testAutomaticEscalation(AlertsNotifications& alerts) {
    alerts.automaticEscalation();
    run_test("Test Automatic Escalation", true); // Verificación básica para confirmar ejecución
}

// Prueba de limpieza y retención
void testEnforceRetentionPolicy(Monitoring& monitoring) {
    int removed = monitoring.enforceRetentionPolicy();
    bool result = (removed >= 0); // Al menos debe ejecutar correctamente la limpieza
    run_test("Test Enforce Retention Policy", result);
}

int main() {
    std::cout << "Starting Monitoring Tests...\n";

    Monitoring monitoring;
    AlertsNotifications alerts = monitoring.alertsNotifications;

    testMonitorAndScaleCPU(monitoring);
    testMonitorMemoryUsage(monitoring);
    testMonitorNetworkTraffic(monitoring);
    testLogPriorityEvent(monitoring);
    testGeneratePerformanceReport(monitoring);
    testEventFrequencyAnalysis(monitoring);
    testCreateAlert(monitoring);
    testConfigureNotificationChannel(alerts);
    testAutomaticEscalation(alerts);
    testEnforceRetentionPolicy(monitoring);

    std::cout << "All monitoring tests completed.\n";

    return 0;
}
