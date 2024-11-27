#ifndef LOGGING_AUDIT_H
#define LOGGING_AUDIT_H

#include <string>
#include <vector>
#include <map>

/**
 * @file logging_audit.h
 * @brief Módulo avanzado de registro y auditoría para MC++.
 *
 * Proporciona funcionalidad para gestionar registros detallados, auditorías
 * críticas y generación de reportes. Diseñado para sistemas que requieren
 * un alto nivel de trazabilidad y control.
 */

// Estructura para representar una entrada de log
struct LogEntry {
    std::string id;                     ///< Identificador único del log
    time_t timestamp;                   ///< Marca de tiempo del log
    std::string level;                  ///< Nivel del log: "INFO", "WARNING", "ERROR", etc.
    std::string source;                 ///< Fuente que generó el log
    std::string message;                ///< Mensaje principal del log
    std::map<std::string, std::string> details; ///< Detalles adicionales del log
};

/**
 * @class LoggingAudit
 * @brief Clase para la gestión avanzada de registros y auditorías en MC++.
 *
 * Ofrece funcionalidades para agregar, filtrar y analizar logs, así como
 * registrar auditorías críticas y exportar datos en formatos estructurados.
 */
class LoggingAudit {
public:
    /**
     * Constructor de la clase.
     * Inicializa los valores predeterminados para políticas de retención.
     */
    LoggingAudit();

    /**
     * Agrega una nueva entrada de log al sistema.
     * @param level Nivel del log ("INFO", "WARNING", "ERROR", etc.).
     * @param source Fuente que genera el log (módulo o función).
     * @param message Mensaje principal del log.
     * @param details Información adicional opcional.
     * @return `true` si el log se agregó correctamente; `false` si el nivel es inválido.
     */
    bool addLog(const std::string& level, const std::string& source, const std::string& message,
                const std::map<std::string, std::string>& details = {});

    /**
     * Filtra logs según nivel y rango de tiempo.
     * @param level Nivel del log a filtrar.
     * @param start_time Tiempo de inicio del rango.
     * @param end_time Tiempo de fin del rango.
     * @return Vector con los logs que cumplen los criterios.
     */
    std::vector<LogEntry> filterLogs(const std::string& level = "INFO", time_t start_time = 0, 
                                     time_t end_time = std::time(nullptr)) const;

    /**
     * Genera un reporte agrupado por nivel y fuente de log.
     * @return Mapa anidado con conteos por nivel y fuente.
     */
    std::map<std::string, std::map<std::string, int>> generateLogReport() const;

    /**
     * Registra un evento de auditoría.
     * @param action Acción ejecutada.
     * @param user Usuario responsable de la acción.
     * @param details Detalles adicionales del evento.
     * @return `true` si se registra exitosamente.
     */
    bool recordAuditEvent(const std::string& action, const std::string& user, 
                          const std::map<std::string, std::string>& details);

    /**
     * Genera un reporte de auditoría.
     * @param user Usuario a filtrar (opcional).
     * @param start_time Tiempo de inicio del rango.
     * @param end_time Tiempo de fin del rango.
     * @return Vector de mapas con los eventos de auditoría que cumplen los criterios.
     */
    std::vector<std::map<std::string, std::string>> generateAuditReport(const std::string& user = "",
                                                                        time_t start_time = 0, 
                                                                        time_t end_time = std::time(nullptr)) const;

    /**
     * Aplica la política de retención para limpiar registros antiguos.
     * @return Número total de registros eliminados.
     */
    int enforceRetentionPolicy();

    /**
     * Exporta los registros y auditorías en formato JSON.
     * @return Cadena JSON con los datos exportados.
     */
    std::string exportLogsAndAudit() const;

    /**
     * Busca logs que contengan un término específico.
     * @param query Término a buscar en los logs.
     * @return Vector con los logs que contienen el término.
     */
    std::vector<LogEntry> searchLogs(const std::string& query) const;

    /**
     * Analiza la frecuencia de eventos en un intervalo de tiempo.
     * @param window Ventana de tiempo en segundos.
     * @return Mapa con la frecuencia de eventos por nivel.
     */
    std::map<std::string, int> eventFrequencyAnalysis(int window = 3600) const;

    /**
     * Activa alertas automáticas para eventos críticos en los logs.
     */
    void triggerAutomaticAlerts();

private:
    std::vector<LogEntry> logEntries; ///< Contenedor de registros de logs.
    std::vector<std::map<std::string, std::string>> auditTrail; ///< Contenedor de auditorías.
    std::map<std::string, std::string> retentionPolicy; ///< Configuración de retención.

    const size_t maxLogs = 10000; ///< Límite máximo de registros.
    const time_t retentionPeriod = 30 * 24 * 60 * 60; ///< Período de retención en segundos.

    /**
     * Registra operaciones internas para depuración y trazabilidad.
     * @param operation Operación ejecutada.
     * @param details Detalles de la operación.
     */
    void logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const;
};

#endif // LOGGING_AUDIT_H
