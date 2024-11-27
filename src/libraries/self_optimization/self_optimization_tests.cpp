#include <cassert>
#include "self_optimization.h"

void testAutoOptimizePerformance() {
    // Configuración de prueba para auto optimización de rendimiento
    std::string process = "critical_process";
    std::map<std::string, float> target = {{"cpu_usage", 0.75}, {"memory_usage", 0.85}};

    bool result = autoOptimizePerformance(process, target);
    assert(result == true);
}

void testIdentifyAndAdjustBottlenecks() {
    // Prueba de identificación y ajuste de cuellos de botella
    std::vector<std::string> optimizedResources = identifyAndAdjustBottlenecks();
    assert(!optimizedResources.empty());
}

void testAdaptiveResourceRelease() {
    // Prueba de liberación adaptativa de recursos
    int resourcesReleased = adaptiveResourceRelease(0.25, 300);
    assert(resourcesReleased >= 0);
}

void testPredictiveResourceScaling() {
    // Prueba de escalado predictivo de recursos
    std::map<std::string, std::vector<float>> history = {
        {"cpu_usage", {0.6, 0.7, 0.85, 0.9}},
        {"memory_usage", {0.5, 0.65, 0.7, 0.8}}
    };
    std::map<std::string, float> thresholds = {{"cpu_usage", 0.85}, {"memory_usage", 0.8}};
    
    bool scaled = predictiveResourceScaling(history, thresholds);
    assert(scaled == true);
}

void testGenerateSelfOptimizedConfig() {
    // Prueba de generación de configuración auto-optimizada
    std::map<std::string, float> optimizedConfig = generateSelfOptimizedConfig();
    assert(!optimizedConfig.empty());
    assert(optimizedConfig.find("cpu_usage") != optimizedConfig.end());
}

void testPerformanceAnalysisFunctions() {
    // Captura de datos de rendimiento
    bool captureResult = capturePerformanceData();
    assert(captureResult == true);

    // Generación de reporte de rendimiento
    std::map<std::string, float> performanceReport = generatePerformanceReport();
    assert(!performanceReport.empty());
    assert(performanceReport.find("average_cpu_usage") != performanceReport.end());
}

void testTunableParametersAdjustment() {
    // Prueba de ajuste automático de parámetros
    addTunableParameter("cpu_allocation", 0.5, 0.2, 0.9, 0.05, "cpu_usage");
    addTunableParameter("memory_allocation", 0.6, 0.2, 0.9, 0.05, "memory_usage");
    
    evaluateAndTuneParameters();

    // Verificación de parámetros ajustados
    std::map<std::string, std::map<std::string, float>> tuningReport = generateTuningReport();
    assert(!tuningReport.empty());
}

void testResourceScaling() {
    // Prueba de escalado y verificación de recursos
    std::map<std::string, float> thresholds = {{"cpu_usage", 0.75}, {"memory_usage", 0.8}};
    bool scalingResult = predictiveResourceScaling({{"cpu_usage", {0.6, 0.8}}, {"memory_usage", {0.65, 0.9}}}, thresholds);
    assert(scalingResult == true);
}

void testAllSelfOptimizationFunctions() {
    testAutoOptimizePerformance();
    testIdentifyAndAdjustBottlenecks();
    testAdaptiveResourceRelease();
    testPredictiveResourceScaling();
    testGenerateSelfOptimizedConfig();
    testPerformanceAnalysisFunctions();
    testTunableParametersAdjustment();
    testResourceScaling();

    std::cout << "All self_optimization tests passed successfully.\n";
}

int main() {
    testAllSelfOptimizationFunctions();
    return 0;
}
