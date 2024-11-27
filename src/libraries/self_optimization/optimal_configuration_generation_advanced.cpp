#include "optimal_configuration_generation_advanced.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <functional>

// Constructor: Inicializa criterios de optimización con valores por defecto
OptimalConfigurationGeneration::OptimalConfigurationGeneration() {
    optimization_criteria = {
        {"cpu_usage", 0.7},
        {"memory_usage", 0.7},
        {"response_time", 150.0}
    };
}

// Genera una configuración del sistema y evalúa su rendimiento
SystemConfiguration OptimalConfigurationGeneration::generateConfiguration(const std::map<std::string, float>& parameter_values) {
    SystemConfiguration config = {
        std::to_string(std::time(nullptr)),  // ID basado en timestamp
        parameter_values,
        measurePerformance(parameter_values),
        0.0f,
        std::time(nullptr)
    };
    config.score = calculateConfigurationScore(config.performance_metrics);
    configuration_history.push_back(config);

    logOperation("generateConfiguration", parameter_values, true);
    return config;
}

// Evalúa métricas de rendimiento para una configuración específica
std::map<std::string, float> OptimalConfigurationGeneration::measurePerformance(const std::map<std::string, float>& parameter_values) {
    // Simulación de métricas para este ejemplo
    return {
        {"cpu_usage", 0.65},
        {"memory_usage", 0.60},
        {"response_time", 140.0}
    };
}

// Calcula la puntuación de una configuración con base en los criterios de optimización
float OptimalConfigurationGeneration::calculateConfigurationScore(const std::map<std::string, float>& performance_metrics) const {
    float score = 0.0f;
    for (const auto& [metric, target] : optimization_criteria) {
        if (performance_metrics.count(metric)) {
            score += 1 - std::abs(target - performance_metrics.at(metric)) / target;
        }
    }
    return score / optimization_criteria.size();  // Normalización
}

// Encuentra la configuración óptima generando combinaciones dentro de los rangos
SystemConfiguration OptimalConfigurationGeneration::findOptimalConfiguration(const std::map<std::string, std::map<std::string, float>>& parameter_ranges) {
    float best_score = -std::numeric_limits<float>::infinity();

    for (const auto& combination : generateParameterCombinations(parameter_ranges)) {
        SystemConfiguration config = generateConfiguration(combination);
        if (config.score > best_score) {
            best_score = config.score;
            optimal_configuration = config;
        }
    }

    logOperation("findOptimalConfiguration", {}, true);
    return optimal_configuration;
}

// Aplica la configuración óptima al sistema
bool OptimalConfigurationGeneration::applyOptimalConfiguration() {
    if (optimal_configuration.parameters.empty()) {
        throw std::runtime_error("No optimal configuration found");
    }
    logOperation("applyOptimalConfiguration", optimal_configuration.parameters, true);
    return true;
}

// Verifica si la configuración óptima sigue siendo efectiva
bool OptimalConfigurationGeneration::verifyOptimalConfiguration() const {
    auto current_metrics = measurePerformance(optimal_configuration.parameters);
    for (const auto& [metric, value] : current_metrics) {
        if (value > optimal_configuration.performance_metrics.at(metric)) {
            logOperation("verifyOptimalConfiguration", {}, false);
            return false;
        }
    }
    logOperation("verifyOptimalConfiguration", {}, true);
    return true;
}

// Genera un reporte de la configuración óptima actual
std::map<std::string, std::map<std::string, float>> OptimalConfigurationGeneration::generateOptimalConfigurationReport() const {
    if (optimal_configuration.parameters.empty()) {
        throw std::runtime_error("No optimal configuration found");
    }
    return {
        {"optimal_parameters", optimal_configuration.parameters},
        {"performance_metrics", optimal_configuration.performance_metrics},
        {"score", {{"score", optimal_configuration.score}}}
    };
}

// Establece nuevos criterios de optimización
void OptimalConfigurationGeneration::setOptimizationCriteria(const std::map<std::string, float>& new_criteria) {
    optimization_criteria = new_criteria;
    logOperation("setOptimizationCriteria", new_criteria, true);
}

// Responde adaptativamente a cambios en el entorno
void OptimalConfigurationGeneration::adaptiveOptimizationResponse() {
    if (!verifyOptimalConfiguration()) {
        auto parameter_ranges = generateParameterRanges();
        optimal_configuration = findOptimalConfiguration(parameter_ranges);
        applyOptimalConfiguration();
    }
    logOperation("adaptiveOptimizationResponse", {}, true);
}

// Genera combinaciones de parámetros dentro de rangos especificados
std::vector<std::map<std::string, float>> OptimalConfigurationGeneration::generateParameterCombinations(const std::map<std::string, std::map<std::string, float>>& parameter_ranges) const {
    std::vector<std::map<std::string, float>> combinations;
    std::vector<std::string> parameters;

    for (const auto& [param, _] : parameter_ranges) {
        parameters.push_back(param);
    }

    std::function<void(size_t, std::map<std::string, float>)> recurse = [&](size_t depth, std::map<std::string, float> current_combination) {
        if (depth == parameters.size()) {
            combinations.push_back(current_combination);
            return;
        }
        const auto& range = parameter_ranges.at(parameters[depth]);
        for (float val = range.at("min"); val <= range.at("max"); val += range.at("step")) {
            current_combination[parameters[depth]] = val;
            recurse(depth + 1, current_combination);
        }
    };

    recurse(0, {});
    return combinations;
}

// Registro de operaciones en el sistema
void OptimalConfigurationGeneration::logOperation(const std::string& operation, const std::map<std::string, float>& parameters, bool success) const {
    std::cout << "[LOG] Operation: " << operation << ", Status: " << (success ? "Success" : "Failure") << std::endl;
    for (const auto& [key, value] : parameters) {
        std::cout << "  " << key << ": " << value << std::endl;
    }
}
