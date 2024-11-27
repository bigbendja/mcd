#ifndef PERFORMANCE_ANALYSIS_ADVANCED_H
#define PERFORMANCE_ANALYSIS_ADVANCED_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <functional>

// Estructura para representar un punto de datos de rendimiento
struct PerformanceDataPoint {
    int timestamp;             // Marca de tiempo en segundos desde época
    float cpu_usage;           // Uso de CPU como porcentaje (0.0 - 1.0)
    float memory_usage;        // Uso de memoria como porcentaje (0.0 - 1.0)
    float disk_io;             // Actividad de disco en MB/s
    float network_io;          // Actividad de red en MB/s
    float response_time;       // Tiempo de respuesta en milisegundos
};

// Estructura para almacenar configuraciones de análisis
struct AnalysisConfig {
    int sample_interval = 60;               // Intervalo en segundos entre muestras
    int retention_period = 86400;           // Período de retención de datos en segundos (24 horas por defecto)
    std::map<std::string, float> alert_thresholds = { // Umbrales predeterminados
        {"cpu", 0.8},
        {"memory", 0.8},
        {"disk_io", 100.0},
        {"network_io", 100.0},
        {"response_time", 200.0}
    };
};

// Clase principal para análisis de rendimiento avanzado
class PerformanceAnalysisAdvanced {
public:
    // Constructor
    PerformanceAnalysisAdvanced();

    // Configuración del análisis
    void setConfig(const AnalysisConfig& config);

    // Captura de datos y análisis
    bool capturePerformanceData();
    int enforceRetentionPolicy();
    std::map<std::string, float> generatePerformanceReport();
    std::vector<std::string> identifyBottlenecks();
    std::vector<std::string> generateAlerts();
    std::map<std::string, float> trendAnalysis(int duration);

    // Ajuste y optimización
    bool adjustAnalysisConfig(const AnalysisConfig& new_config);
    void autoOptimize();

private:
    AnalysisConfig config_;                           // Configuración activa
    std::list<PerformanceDataPoint> performance_data_; // Datos de rendimiento capturados

    // Métodos utilitarios
    float calculateAverage(const std::function<float(const PerformanceDataPoint&)>& metric) const;
    float calculatePeak(const std::function<float(const PerformanceDataPoint&)>& metric) const;
    float calculateTrend(const std::list<PerformanceDataPoint>& data,
                         const std::function<float(const PerformanceDataPoint&)>& metric) const;
    
    void logOperation(const std::string& operation, const std::map<std::string, float>& details) const;
    void sendAlert(const std::string& title, const std::vector<std::string>& messages) const;
};

#endif // PERFORMANCE_ANALYSIS_ADVANCED_H
