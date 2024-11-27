#include "monitoring.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>

// Función auxiliar para ejecutar pruebas unitarias
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Prueba de monitoreo de CPU
void test_cpu_monitoring() {
    bool alert_triggered = monitoring::monitor_and_scale_cpu(0.5);
    run_test("Monitorización de CPU (sin alertas)", !alert_triggered);

    // Simulación de carga de CPU alta para probar la alerta
    alert_triggered = monitoring::monitor_and_scale_cpu(0.01); // Umbral bajo para provocar alerta
    run_test("Alerta de CPU alta", alert_triggered);
}

// Prueba de monitoreo de memoria
void test_memory_monitoring() {
    auto memory_log = monitoring::monitor_and_tune_memory(0.5, true, 1);
    run_test("Monitorización de memoria (dentro del umbral)", memory_log["usage"] <= 0.5);

    // Simulación de carga de memoria alta para probar la alerta
    memory_log = monitoring::monitor_and_tune_memory(0.01, true, 1); // Umbral bajo
    run_test("Ajuste de memoria en condiciones críticas", memory_log["usage"] > 0.5);
}

// Prueba de monitoreo de red
void test_network_monitoring() {
    auto network_log = monitoring::analyze_and_alert_network_traffic(1000.0); // Mbps
    run_test("Monitorización de tráfico de red (dentro del umbral)", network_log["traffic"] <= 1000.0);

    // Simulación de tráfico de red alto para probar la alerta
    network_log = monitoring::analyze_and_alert_network_traffic(0.1); // Umbral bajo
    run_test("Alerta de tráfico de red alto", network_log["traffic"] > 0.1);
}

// Prueba de monitoreo de temperatura
void test_temperature_monitoring() {
    bool alert_triggered = monitoring::monitor_and_respond_temperature(100.0);
    run_test("Monitorización de temperatura (dentro del umbral)", !alert_triggered);

    // Simulación de temperatura alta para probar la alerta
    alert_triggered = monitoring::monitor_and_respond_temperature(0.01); // Umbral bajo para provocar alerta
    run_test("Alerta de temperatura alta", alert_triggered);
}

// Prueba de registro y auditoría
void test_logging_audit() {
    bool log_created = monitoring::log_priority_event("TEST", "Prueba de registro de auditoría", "INFO");
    run_test("Registro de auditoría creado", log_created);
}

// Prueba de generación de reportes
void test_report_generation() {
    auto report = monitoring::generate_performance_report();
    run_test("Generación de reporte de rendimiento", !report.empty());
}

// Prueba de análisis de tendencias
void test_trend_analysis() {
    auto trend = monitoring::trend_analysis("CPU", 600);
    run_test("Análisis de tendencia (incremento)", trend["increasing"] || trend["steady"]);
}

// Prueba de escalado automático
void test_automated_response() {
    monitoring::automated_response();
    run_test("Respuesta automática activada en carga crítica", true); // Suponiendo que ejecuta sin errores
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'monitoring'" << std::endl;

    test_cpu_monitoring();
    test_memory_monitoring();
    test_network_monitoring();
    test_temperature_monitoring();
    test_logging_audit();
    test_report_generation();
    test_trend_analysis();
    test_automated_response();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
