#ifndef PERFORMANCE_MONITORING_H
#define PERFORMANCE_MONITORING_H

#include <string>
#include <map>
#include <list>
#include <vector>
#include <ctime>

// Estructura para representar una métrica de rendimiento
struct PerformanceMetric {
    std::string id;              // Identificador único de la métrica
    std::string type;            // Tipo de recurso (CPU, memory, disk, etc.)
    float usage;                 // Uso actual como porcentaje (0.0 a 1.0)
    float average_usage;         // Uso promedio ponderado
    float peak_usage;            // Uso máximo alcanzado
    float min_usage;             // Uso mínimo observado
    std::time_t timestamp;       // Marca de tiempo de la última actualización
};

// Clase avanzada de monitoreo de rendimiento
class PerformanceMonitoring {
public:
    // Constructor
    PerformanceMonitoring();

    // Agrega una métrica de rendimiento a monitorear
    bool addPerformanceMetric(const std::string& id, const std::string& type);

    // Actualiza el uso de una métrica específica
    bool updateMetricUsage(const std::string& id, float usage);

    // Verifica si las métricas superan umbrales definidos y retorna alertas
    std::vector<std::map<std::string, std::string>> checkAlertThresholds();

    // Inicia el monitoreo de rendimiento continuo en intervalos específicos
    void startMonitoring(int interval = 300);

    // Genera un reporte detallado de las métricas de rendimiento
    std::map<std::string, std::map<std::string, float>> generatePerformanceReport();

    // Visualiza las métricas en tiempo real
    void displayRealTimeMetrics();

    // Monitorea una aplicación específica según umbrales personalizados
    void monitorApplication(const std::string& id, float cpu_threshold, float memory_threshold);

    // Analiza tendencias para detectar patrones en las métricas de uso
    std::map<std::string, bool> trendAnalysis(const std::string& metric_id, int duration);

    // Ajusta recursos automáticamente en respuesta a las tendencias observadas
    void automatedResponse();

    // Escala un recurso hacia arriba en función de la métrica de uso
    bool scaleUpResource(const std::string& id);

    // Escala un recurso hacia abajo en función de la métrica de uso
    bool scaleDownResource(const std::string& id);

private:
    std::list<PerformanceMetric> performanceMetrics;         // Lista de métricas de rendimiento
    std::map<std::string, float> alertThresholds;            // Umbrales de alerta para cada tipo de recurso
    void logOperation(const std::string& operation, const std::map<std::string, std::string>& details); // Función de auditoría interna
};

#endif // PERFORMANCE_MONITORING_H
