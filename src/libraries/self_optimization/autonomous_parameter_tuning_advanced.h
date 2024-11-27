#ifndef AUTONOMOUS_PARAMETER_TUNING_ADVANCED_H
#define AUTONOMOUS_PARAMETER_TUNING_ADVANCED_H

#include <string>
#include <map>
#include <vector>

// -------------------- Estructuras --------------------

// Representa un parámetro ajustable con sus atributos principales
struct TunableParameter {
    std::string name;             // Nombre del parámetro
    float value;                  // Valor actual del parámetro
    float min_value;              // Valor mínimo permitido
    float max_value;              // Valor máximo permitido
    float adjustment_step;        // Incremento o decremento del ajuste
    std::string target_metric;    // Métrica objetivo asociada
};

// Configura las políticas de ajuste para los parámetros
struct TuningPolicy {
    int tuning_interval;          // Intervalo (en segundos) entre ajustes
    int stabilization_period;     // Tiempo de estabilización (en segundos)
    float tolerance;              // Tolerancia permitida en la variación
};

// -------------------- Clase Principal --------------------

class AutonomousParameterTuning {
public:
    // Constructor para inicializar la configuración por defecto
    AutonomousParameterTuning();

    // -------------------- Gestión de Parámetros --------------------

    // Añade un nuevo parámetro ajustable al sistema
    bool addTunableParameter(const std::string& name, float initial_value, float min_value, float max_value,
                             float adjustment_step, const std::string& target_metric);

    // Incrementa o decrementa el valor de un parámetro dentro de sus límites
    bool increaseParameter(TunableParameter& parameter);
    bool decreaseParameter(TunableParameter& parameter);

    // Aplica un nuevo valor ajustado a un parámetro en el sistema
    bool applyParameter(const std::string& parameter_name, float new_value);

    // -------------------- Políticas de Ajuste --------------------

    // Configura las políticas de ajuste autónomo
    bool setTuningPolicy(int tuning_interval, int stabilization_period, float tolerance);

    // -------------------- Operaciones Autónomas --------------------

    // Evalúa y ajusta automáticamente los parámetros en función de métricas objetivo
    void evaluateAndTuneParameters();

    // Inicia el ciclo de ajuste autónomo en intervalos definidos
    void startAutonomousTuning(int interval = 60);

    // Realiza optimizaciones adaptativas basadas en patrones históricos
    void adaptiveOptimization();

    // -------------------- Análisis y Reportes --------------------

    // Genera un reporte detallado sobre el estado actual de los parámetros
    std::map<std::string, std::map<std::string, float>> generateTuningReport() const;

    // Verifica la estabilidad de un parámetro basado en datos históricos
    bool verifyStability(const TunableParameter& parameter) const;

private:
    // -------------------- Atributos --------------------

    std::vector<TunableParameter> tunable_parameters;  // Lista de parámetros ajustables
    TuningPolicy tuning_policy;                        // Política de ajuste autónomo

    // -------------------- Funciones Internas --------------------

    // Calcula el valor óptimo para un parámetro según datos históricos
    float findOptimalValue(const std::vector<float>& historical_data, float min_value, float max_value) const;

    // Obtiene datos históricos de una métrica para análisis
    std::vector<float> getHistoricalMetricData(const std::string& metric, int duration) const;

    // Evalúa si los datos históricos son estables según la tolerancia configurada
    bool isStable(const std::vector<float>& historical_data, float tolerance) const;

    // Registra operaciones importantes en el sistema de ajuste
    void logOperation(const std::string& operation, const std::string& parameter_name,
                      float new_value, bool success) const;
};

#endif // AUTONOMOUS_PARAMETER_TUNING_ADVANCED_H
