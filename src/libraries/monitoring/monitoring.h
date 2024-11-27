#ifndef MONITORING_H
#define MONITORING_H

#include "performance_monitoring.h"
#include "logging_audit.h"
#include "alerts_notifications.h"

/**
 * @class Monitoring
 * @brief Clase principal para la gestión centralizada de monitoreo en MC++.
 * 
 * Esta clase integra módulos de monitoreo de rendimiento, auditoría de eventos, y gestión de alertas.
 * Ofrece un control unificado para la supervisión y mejora del rendimiento de sistemas complejos.
 */
class Monitoring {
public:
    /**
     * @brief Constructor de la clase Monitoring.
     * Inicializa los módulos y configura las políticas necesarias.
     */
    Monitoring();

    // Funciones de inicialización de los módulos
    void initializePerformanceMonitoring();
    void initializeLoggingAudit();
    void initializeAlertsNotifications();

    // Funciones principales de monitoreo (delegan a los módulos)
    
    /**
     * @brief Monitorea el uso de CPU y ajusta recursos según el umbral.
     * @param threshold Umbral de uso permitido (0.0 a 1.0).
     * @return true si se ajustaron los recursos correctamente.
     */
    bool monitorAndScaleCPU(float threshold);

    /**
     * @brief Monitorea el uso de memoria con opción de optimización.
     * @param threshold Umbral de uso permitido (0.0 a 1.0).
     * @param optimize Indica si se aplicarán optimizaciones automáticas.
     * @return Mapa con métricas de uso de memoria.
     */
    std::map<std::string, float> monitorMemoryUsage(float threshold, bool optimize);

    /**
     * @brief Monitorea el tráfico de red y alerta si supera el ancho de banda permitido.
     * @param maxBandwidth Ancho de banda máximo permitido (Mbps).
     * @return true si el monitoreo se realizó correctamente.
     */
    bool monitorNetworkTraffic(float maxBandwidth);

    /**
     * @brief Registra un evento prioritario en los logs del sistema.
     * @param eventType Tipo de evento.
     * @param description Descripción del evento.
     * @param priority Nivel de prioridad ("LOW", "MEDIUM", "HIGH").
     * @return true si el evento se registró correctamente.
     */
    bool logPriorityEvent(const std::string& eventType, const std::string& description, const std::string& priority);

    /**
     * @brief Crea una alerta y envía notificaciones a los canales configurados.
     * @param type Tipo de alerta (CPU, Memory, Disk, etc.).
     * @param severity Nivel de severidad ("INFO", "WARNING", "CRITICAL").
     * @param message Mensaje descriptivo de la alerta.
     * @return true si la alerta fue creada y notificada correctamente.
     */
    bool createAlert(const std::string& type, const std::string& severity, const std::string& message);

    // Generación de reportes y auditoría

    /**
     * @brief Genera un reporte de alertas agrupadas por tipo y severidad.
     * @return Mapa de estadísticas de alertas.
     */
    std::map<std::string, std::map<std::string, int>> generateAlertReport();

    /**
     * @brief Realiza un análisis de frecuencia de eventos en un período de tiempo.
     * @param window Ventana de tiempo en segundos.
     * @return Mapa con frecuencias de eventos por tipo.
     */
    std::map<std::string, int> eventFrequencyAnalysis(int window);

    // Limpieza y retención de registros

    /**
     * @brief Aplica políticas de retención a logs y alertas antiguas.
     * @return Número total de registros eliminados.
     */
    int enforceRetentionPolicy();

    /**
     * @brief Limpia alertas antiguas o reconocidas.
     * @return Número de alertas eliminadas.
     */
    int cleanupOldAlerts();

    /**
     * @brief Exporta un reporte combinado de rendimiento, logs y alertas en formato JSON.
     * @return Cadena JSON representando el reporte.
     */
    std::string exportMonitoringReport();

private:
    PerformanceMonitoring performanceMonitoring;  ///< Módulo de monitoreo de rendimiento.
    LoggingAudit loggingAudit;                    ///< Módulo de auditoría de eventos y logs.
    AlertsNotifications alertsNotifications;      ///< Módulo de gestión de alertas.

    // Funciones auxiliares para configuraciones internas

    /**
     * @brief Configura las políticas y umbrales de monitoreo.
     */
    void configureMonitoringSettings();
};

#endif // MONITORING_H
