#include <iostream>
#include "utils/logger.h"
#include "utils/config.h"
#include "math/math_operations.h"
#include "ai_ml/ai_model.h"
#include "adaptive_optimization/load_balancing.h"
#include "security/encryption.h"
#include "monitoring/performance_monitoring.h"

int main() {
    // Inicialización básica
    std::cout << "Iniciando MC++..." << std::endl;

    // Cargar configuración general del sistema
    config::loadConfig("config.json");
    std::cout << "Configuración cargada exitosamente." << std::endl;

    // Ejemplo de uso de los módulos disponibles
    // 1. Ejemplo de operaciones matemáticas
    double resultado = math::add(5.0, 3.0);
    std::cout << "Resultado de la suma: " << resultado << std::endl;

    // 2. Ejemplo de balanceo de carga
    load_balancing::balance("ProcesoEjemplo");

    // 3. Ejemplo de uso de un modelo de IA
    ai_ml::Model modelo;
    modelo.train();

    // 4. Ejemplo de encriptación
    std::string mensaje_encriptado = security::encrypt("mensaje de ejemplo");
    std::cout << "Mensaje encriptado: " << mensaje_encriptado << std::endl;

    // 5. Ejemplo de monitoreo de rendimiento
    monitoring::PerformanceMonitor monitor;
    monitor.logPerformance();

    // Cerrar la aplicación
    std::cout << "MC++ finalizado." << std::endl;
    return 0;
}
