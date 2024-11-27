#include "adaptive_optimization.h"
#include <cassert>
#include <iostream>
#include <vector>

// Test de la función de balanceo de carga dinámico
void test_dynamic_load_balance() {
    std::vector<std::string> nodes = {"Node1", "Node2", "Node3"};
    std::string process = "critical_process";
    std::string selected_node = DYNAMIC_LOAD_BALANCE(nodes, process, 0.8);
    
    assert(!selected_node.empty() && "El balanceo de carga debería seleccionar un nodo.");
    std::cout << "Prueba 'test_dynamic_load_balance' pasada." << std::endl;
}

// Test de la asignación dinámica de CPU
void test_dynamic_cpu_allocation() {
    std::string process = "CPU_critical_process";
    bool success = DYNAMIC_CPU_ALLOCATION(process, 0.85);

    assert(success && "La asignación de CPU debería ser exitosa.");
    std::cout << "Prueba 'test_dynamic_cpu_allocation' pasada." << std::endl;
}

// Test de la liberación de recursos no utilizados
void test_smart_resource_release() {
    int freed_resources = SMART_RESOURCE_RELEASE(300, "MEMORY");

    assert(freed_resources >= 0 && "La función debe liberar recursos inactivos según el umbral.");
    std::cout << "Prueba 'test_smart_resource_release' pasada." << std::endl;
}

// Test de ajuste predictivo de memoria
void test_predictive_memory_tuning() {
    bool success = PREDICTIVE_MEMORY_TUNING(0.8, 0.1);

    assert(success && "La optimización predictiva de memoria debería completarse correctamente.");
    std::cout << "Prueba 'test_predictive_memory_tuning' pasada." << std::endl;
}

// Test de proyección de carga basada en ML
void test_ml_load_projection() {
    std::vector<float> history = {0.6, 0.7, 0.75, 0.8};
    float predicted_load = ML_LOAD_PROJECTION(history, "LINEAR");

    assert(predicted_load > 0 && "La proyección de carga debería calcular un valor positivo.");
    std::cout << "Prueba 'test_ml_load_projection' pasada." << std::endl;
}

// Test de inicialización de Adaptive Optimization
void test_initialize_adaptive_optimization() {
    assert(INITIALIZE_ADAPTIVE_OPTIMIZATION() && "La inicialización de Adaptive Optimization debería completarse exitosamente.");
    std::cout << "Prueba 'test_initialize_adaptive_optimization' pasada." << std::endl;
}

// Test de monitoreo en tiempo real
void test_real_time_monitoring() {
    EXECUTE_REAL_TIME_MONITORING(); // Esta función debería ejecutar sin errores
    std::cout << "Prueba 'test_real_time_monitoring' pasada." << std::endl;
}

// Test de predicción de carga
void test_execute_load_prediction() {
    assert(EXECUTE_LOAD_PREDICTION() && "La predicción de carga debería ejecutarse correctamente.");
    std::cout << "Prueba 'test_execute_load_prediction' pasada." << std::endl;
}

// Test de validación de configuraciones
void test_validate_configurations() {
    assert(VALIDATE_CONFIGURATIONS() && "Las configuraciones deben validarse correctamente.");
    std::cout << "Prueba 'test_validate_configurations' pasada." << std::endl;
}

// Test de finalización de Adaptive Optimization
void test_terminate_adaptive_optimization() {
    assert(TERMINATE_ADAPTIVE_OPTIMIZATION() && "La finalización de Adaptive Optimization debería completarse exitosamente.");
    std::cout << "Prueba 'test_terminate_adaptive_optimization' pasada." << std::endl;
}

// Función principal para ejecutar todas las pruebas
int main() {
    std::cout << "Iniciando pruebas para la librería adaptive_optimization...\n";

    // Ejecución de pruebas individuales
    test_dynamic_load_balance();
    test_dynamic_cpu_allocation();
    test_smart_resource_release();
    test_predictive_memory_tuning();
    test_ml_load_projection();
    test_initialize_adaptive_optimization();
    test_real_time_monitoring();
    test_execute_load_prediction();
    test_validate_configurations();
    test_terminate_adaptive_optimization();

    std::cout << "Todas las pruebas de 'adaptive_optimization' han pasado exitosamente.\n";
    return 0;
}
