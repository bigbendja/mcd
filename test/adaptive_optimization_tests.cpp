#include "adaptive_optimization.h"
#include "config.h"
#include <cassert>
#include <iostream>

// Función auxiliar para ejecutar y verificar los resultados de las pruebas
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas para el balanceo de carga dinámico
void test_dynamic_load_balance() {
    std::vector<std::string> nodes = {"Node1", "Node2", "Node3"};
    std::string assigned_node = adaptive_optimization::dynamicLoadBalance(nodes, "critical_process", 0.75);

    run_test("Balanceo de carga dinámico asigna un nodo disponible", !assigned_node.empty());
    run_test("Nodo asignado está en la lista", std::find(nodes.begin(), nodes.end(), assigned_node) != nodes.end());
}

// Pruebas para el ajuste dinámico de CPU
void test_dynamic_cpu_allocation() {
    bool allocation_result = adaptive_optimization::dynamicCpuAllocation("high_priority_process", 0.8);
    run_test("Ajuste dinámico de CPU exitoso", allocation_result);
}

// Pruebas de liberación inteligente de recursos no utilizados
void test_smart_resource_release() {
    int resources_freed = adaptive_optimization::smartResourceRelease(300, "memory");
    run_test("Liberación inteligente de recursos (memoria)", resources_freed > 0);
}

// Pruebas de optimización predictiva de memoria
void test_predictive_memory_tuning() {
    bool tuning_result = adaptive_optimization::predictiveMemoryTuning(0.8, 0.05);
    run_test("Optimización predictiva de memoria", tuning_result);
}

// Pruebas de proyección de carga basada en ML
void test_ml_load_projection() {
    std::vector<double> history = {0.5, 0.6, 0.7, 0.8};
    double projected_load = adaptive_optimization::mlLoadProjection(history, "linear");

    run_test("Proyección de carga basada en ML (lineal)", projected_load > 0);
}

// Pruebas de configuración y parámetros de optimización
void test_optimization_config() {
    config::load_config("./config/adaptive_optimization_config.json");

    double scale_up_threshold = config::get_setting<double>("scaling.scale_up_threshold");
    run_test("Verificación de umbral de escalado hacia arriba desde configuración", scale_up_threshold == 0.8);

    int cooldown_period = config::get_setting<int>("scaling.cooldown_period");
    run_test("Verificación del periodo de enfriamiento", cooldown_period == 300);
}

// Pruebas de escalado predictivo
void test_predictive_scaling() {
    adaptive_optimization::enablePredictiveScaling(true);
    bool scaling_result = adaptive_optimization::predictiveScaling();

    run_test("Escalado predictivo habilitado y exitoso", scaling_result);
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'adaptive_optimization'" << std::endl;

    test_dynamic_load_balance();
    test_dynamic_cpu_allocation();
    test_smart_resource_release();
    test_predictive_memory_tuning();
    test_ml_load_projection();
    test_optimization_config();
    test_predictive_scaling();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
