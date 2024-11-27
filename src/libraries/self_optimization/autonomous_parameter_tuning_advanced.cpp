#include "autonomous_parameter_tuning_advanced.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>

// Añadir un nuevo parámetro ajustable
bool AutonomousParameterTuning::addTunableParameter(const std::string& name, float initial_value, float min_value, float max_value, float adjustment_step, const std::string& target_metric) {
    if (min_value >= max_value || adjustment_step <= 0) {
        logOperation("ADD_TUNABLE_PARAMETER_FAILED", {{"name", name}, {"reason", "Invalid parameter range or step size"}}, false);
        return false;
    }

    TunableParameter parameter = {name, initial_value, min_value, max_value, adjustment_step, target_metric};
    tunable_parameters.push_back(parameter);
    logOperation("ADD_TUNABLE_PARAMETER", {{"name", name}, {"initial_value", initial_value}, {"target_metric", target_metric}}, true);
    return true;
}

// Evaluar y ajustar parámetros
void AutonomousParameterTuning::evaluateAndTuneParameters() {
    for (auto& parameter : tunable_parameters) {
        float current_performance = getCurrentMetric(parameter.target_metric);
        float target_value = getTargetMetric(parameter.target_metric);

        if (current_performance > target_value * (1 + tuning_policy.tolerance)) {
            decreaseParameter(parameter);
        } else if (current_performance < target_value * (1 - tuning_policy.tolerance)) {
            increaseParameter(parameter);
        }

        logOperation("EVALUATE_AND_TUNE_PARAMETERS", parameter.name, {{"current_performance", current_performance}, {"target_value", target_value}}, parameter.value);
    }
}

// Disminuir el valor de un parámetro
bool AutonomousParameterTuning::decreaseParameter(TunableParameter& parameter) {
    if (parameter.value > parameter.min_value + parameter.adjustment_step) {
        parameter.value -= parameter.adjustment_step;
        applyParameter(parameter.name, parameter.value);
        logOperation("DECREASE_PARAMETER", parameter.name, {{"new_value", parameter.value}}, true);
        return true;
    }
    logOperation("DECREASE_PARAMETER_FAILED", parameter.name, {}, false);
    return false;
}

// Incrementar el valor de un parámetro
bool AutonomousParameterTuning::increaseParameter(TunableParameter& parameter) {
    if (parameter.value < parameter.max_value - parameter.adjustment_step) {
        parameter.value += parameter.adjustment_step;
        applyParameter(parameter.name, parameter.value);
        logOperation("INCREASE_PARAMETER", parameter.name, {{"new_value", parameter.value}}, true);
        return true;
    }
    logOperation("INCREASE_PARAMETER_FAILED", parameter.name, {}, false);
    return false;
}

// Aplicar un valor ajustado de parámetro
bool AutonomousParameterTuning::applyParameter(const std::string& parameter_name, float new_value) {
    bool success = systemApplyParameter(parameter_name, new_value);
    logOperation("APPLY_PARAMETER", {{"parameter_name", parameter_name}, {"new_value", new_value}}, success);
    return success;
}

// Ciclo de ajuste autónomo
void AutonomousParameterTuning::startAutonomousTuning(int interval) {
    while (true) {
        evaluateAndTuneParameters();
        logOperation("AUTONOMOUS_TUNING_CYCLE", {}, {{"interval", interval}}, true);
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

// Generar reporte de ajuste
std::map<std::string, std::map<std::string, float>> AutonomousParameterTuning::generateTuningReport() const {
    std::map<std::string, std::map<std::string, float>> report;
    for (const auto& parameter : tunable_parameters) {
        report[parameter.name] = {
            {"current_value", parameter.value},
            {"min_value", parameter.min_value},
            {"max_value", parameter.max_value},
            {"target_metric", getCurrentMetric(parameter.target_metric)}
        };
    }
    logOperation("GENERATE_TUNING_REPORT", {}, {}, true);
    return report;
}

// Ajustar política de ajuste autónomo
bool AutonomousParameterTuning::setTuningPolicy(int tuning_interval, int stabilization_period, float tolerance) {
    if (tuning_interval <= 0 || stabilization_period <= 0 || tolerance <= 0) {
        logOperation("SET_TUNING_POLICY_FAILED", {}, {}, false);
        return false;
    }
    tuning_policy = {tuning_interval, stabilization_period, tolerance};
    logOperation("SET_TUNING_POLICY", {}, {{"tuning_interval", tuning_interval}, {"stabilization_period", stabilization_period}, {"tolerance", tolerance}}, true);
    return true;
}

// Verificar estabilidad después de ajustes
bool AutonomousParameterTuning::verifyStability(const TunableParameter& parameter) const {
    auto historical_data = getHistoricalMetricData(parameter.target_metric, tuning_policy.stabilization_period);
    bool stable = isStable(historical_data, tuning_policy.tolerance);
    logOperation("VERIFY_STABILITY", parameter.name, {{"stabilization_period", tuning_policy.stabilization_period}, {"tolerance", tuning_policy.tolerance}}, stable);
    return stable;
}

// Optimización adaptativa basada en patrones históricos
void AutonomousParameterTuning::adaptiveOptimization() {
    for (auto& parameter : tunable_parameters) {
        auto historical_performance = getHistoricalMetricData(parameter.target_metric, tuning_policy.stabilization_period);
        float optimal_value = findOptimalValue(historical_performance, parameter.min_value, parameter.max_value);
        parameter.value = optimal_value;
        applyParameter(parameter.name, optimal_value);
        logOperation("ADAPTIVE_OPTIMIZATION", parameter.name, {{"optimal_value", optimal_value}}, parameter.value);
    }
}

// Obtener métrica actual para un parámetro objetivo
float AutonomousParameterTuning::getCurrentMetric(const std::string& metric) const {
    return simulateCurrentMetric(metric);  // Placeholder for actual metric retrieval
}

// Obtener el valor objetivo para una métrica
float AutonomousParameterTuning::getTargetMetric(const std::string& metric) const {
    return target_metrics.at(metric);  // Fetch target metric value
}

// Verificar estabilidad en los datos históricos
bool AutonomousParameterTuning::isStable(const std::vector<float>& historical_data, float tolerance) const {
    float average = std::accumulate(historical_data.begin(), historical_data.end(), 0.0f) / historical_data.size();
    return std::all_of(historical_data.begin(), historical_data.end(), [&](float value) {
        return std::fabs(value - average) <= tolerance;
    });
}

// Registrar operación en el sistema de logs
void AutonomousParameterTuning::logOperation(const std::string& operation, const std::map<std::string, float>& parameters, bool success) const {
    std::cout << "Operación: " << operation << " - Estado: " << (success ? "Éxito" : "Fallo") << "\n";
}
