#include "self_optimization.h"
#include <cassert>
#include <iostream>

// Función auxiliar para ejecutar y mostrar resultados de pruebas unitarias
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Prueba de optimización de uso de CPU
void test_cpu_optimization() {
    float initial_usage = 0.85;  // Simulación de alta carga
    self_optimization::optimize_cpu_usage(initial_usage);

    float optimized_usage = self_optimization::get_cpu_usage();
    run_test("Optimización de uso de CPU", optimized_usage < initial_usage);
}

// Prueba de optimización de uso de memoria
void test_memory_optimization() {
    float initial_usage = 0.90;  // Simulación de alta carga de memoria
    self_optimization::optimize_memory_usage(initial_usage);

    float optimized_usage = self_optimization::get_memory_usage();
    run_test("Optimización de uso de memoria", optimized_usage < initial_usage);
}

// Prueba de gestión de cache
void test_cache_management() {
    self_optimization::enable_cache();
    run_test("Habilitar caché", self_optimization::is_cache_enabled());

    self_optimization::set_cache_size_limit(50);  // Limitar el tamaño de caché a 50 MB
    run_test("Configurar límite de tamaño de caché", self_optimization::get_cache_size_limit() == 50);
    
    self_optimization::clear_cache();
    run_test("Limpiar caché", self_optimization::get_cache_size() == 0);
}

// Prueba de balanceo de carga autónomo
void test_autonomous_load_balancing() {
    self_optimization::start_load_balancing();
    bool balancing_active = self_optimization::is_load_balancing_active();
    run_test("Balanceo de carga activo", balancing_active);

    // Simulación de carga de nodos para ver balanceo
    self_optimization::set_node_load("NodeA", 0.95);
    self_optimization::set_node_load("NodeB", 0.20);
    std::string balanced_node = self_optimization::get_least_loaded_node();
    
    run_test("Nodo con menor carga", balanced_node == "NodeB");
    self_optimization::stop_load_balancing();
}

// Prueba de optimización de red
void test_network_optimization() {
    float initial_bandwidth = 0.9;  // Simulación de alta carga de red
    self_optimization::optimize_network_usage(initial_bandwidth);

    float optimized_bandwidth = self_optimization::get_network_usage();
    run_test("Optimización de uso de red", optimized_bandwidth < initial_bandwidth);
}

// Prueba de monitoreo y ajuste dinámico
void test_dynamic_adjustment() {
    self_optimization::enable_dynamic_adjustment();
    run_test("Habilitar ajuste dinámico", self_optimization::is_dynamic_adjustment_enabled());

    self_optimization::adjust_resource_limits(0.8);
    run_test("Ajuste de límite de recursos", self_optimization::get_resource_limit_factor() == 0.8);

    self_optimization::disable_dynamic_adjustment();
    run_test("Deshabilitar ajuste dinámico", !self_optimization::is_dynamic_adjustment_enabled());
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'self_optimization'" << std::endl;

    test_cpu_optimization();
    test_memory_optimization();
    test_cache_management();
    test_autonomous_load_balancing();
    test_network_optimization();
    test_dynamic_adjustment();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
