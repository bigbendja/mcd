#ifndef OPTIMAL_CONFIGURATION_GENERATION_ADVANCED_H
#define OPTIMAL_CONFIGURATION_GENERATION_ADVANCED_H

#include <string>
#include <map>
#include <vector>
#include <ctime>

/**
 * @file optimal_configuration_generation_advanced.h
 * @brief Definición de clases y métodos para la generación y evaluación de configuraciones óptimas del sistema.
 *
 * Este módulo permite generar configuraciones de parámetros del sistema, evaluarlas en base
 * a métricas de rendimiento, y aplicar la configuración óptima para maximizar la eficiencia.
 */

/** 
 * @struct SystemConfiguration
 * @brief Representa una configuración del sistema con métricas asociadas.
 */
struct SystemConfiguration {
    std::string id;                                   ///< Identificador único de la configuración.
    std::map<std::string, float> parameters;          ///< Valores de parámetros del sistema.
    std::map<std::string, float> performance_metrics; ///< Métricas de rendimiento evaluadas.
    time_t timestamp;                                 ///< Marca temporal de la configuración.
    float score;                                      ///< Puntuación basada en criterios de optimización.
};

/** 
 * @class OptimalConfigurationGeneration
 * @brief Genera, evalúa y aplica configuraciones óptimas del sistema.
 */
class OptimalConfigurationGeneration {
public:
    /** Constructor: Inicializa criterios de optimización por defecto. */
    OptimalConfigurationGeneration();

    /**
     * @brief Genera una configuración específica basada en valores de parámetros.
     * @param parameter_values Mapa de valores de parámetros.
     * @return SystemConfiguration La configuración generada.
     */
    SystemConfiguration generateConfiguration(const std::map<std::string, float>& parameter_values);

    /**
     * @brief Evalúa el rendimiento de una configuración y devuelve las métricas.
     * @param parameter_values Mapa de valores de parámetros.
     * @return std::map<std::string, float> Métricas de rendimiento.
     */
    std::map<std::string, float> measurePerformance(const std::map<std::string, float>& parameter_values);

    /**
     * @brief Calcula la puntuación de una configuración según criterios de optimización.
     * @param performance_metrics Mapa de métricas de rendimiento.
     * @return float Puntuación de la configuración.
     */
    float calculateConfigurationScore(const std::map<std::string, float>& performance_metrics) const;

    /**
     * @brief Encuentra la configuración óptima dentro de los rangos especificados.
     * @param parameter_ranges Rango de valores para cada parámetro.
     * @return SystemConfiguration La configuración óptima encontrada.
     */
    SystemConfiguration findOptimalConfiguration(const std::map<std::string, std::map<std::string, float>>& parameter_ranges);

    /**
     * @brief Aplica la configuración óptima encontrada al sistema.
     * @return true Si la aplicación fue exitosa, false en caso contrario.
     */
    bool applyOptimalConfiguration();

    /**
     * @brief Verifica si la configuración óptima sigue siendo válida.
     * @return true Si la configuración sigue siendo óptima, false en caso contrario.
     */
    bool verifyOptimalConfiguration() const;

    /**
     * @brief Genera un reporte detallado sobre la configuración óptima actual.
     * @return std::map<std::string, std::map<std::string, float>> Reporte de configuración.
     */
    std::map<std::string, std::map<std::string, float>> generateOptimalConfigurationReport() const;

    /**
     * @brief Establece nuevos criterios de optimización.
     * @param new_criteria Mapa con los nuevos criterios.
     */
    void setOptimizationCriteria(const std::map<std::string, float>& new_criteria);

    /**
     * @brief Ajusta la configuración de manera adaptativa ante cambios en el entorno.
     */
    void adaptiveOptimizationResponse();

private:
    SystemConfiguration optimal_configuration;                   ///< Configuración óptima actual.
    std::vector<SystemConfiguration> configuration_history;      ///< Historial de configuraciones generadas.
    std::map<std::string, float> optimization_criteria;          ///< Criterios de optimización actuales.

    /**
     * @brief Genera todas las combinaciones de parámetros en los rangos especificados.
     * @param parameter_ranges Rango de valores para cada parámetro.
     * @return std::vector<std::map<std::string, float>> Lista de combinaciones posibles.
     */
    std::vector<std::map<std::string, float>> generateParameterCombinations(const std::map<std::string, std::map<std::string, float>>& parameter_ranges) const;

    /**
     * @brief Registra operaciones realizadas para seguimiento y auditoría.
     * @param operation Nombre de la operación.
     * @param parameters Parámetros relacionados con la operación.
     * @param success Indica si la operación fue exitosa.
     */
    void logOperation(const std::string& operation, const std::map<std::string, float>& parameters, bool success) const;
};

#endif // OPTIMAL_CONFIGURATION_GENERATION_ADVANCED_H
