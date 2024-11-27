#ifndef ADAPTIVE_OPTIMIZATION_H
#define ADAPTIVE_OPTIMIZATION_H

#include "load_balancing.h"
#include "resource_release.h"
#include "autonomous_scaling_adjustment.h"

// Estructura para representar el estado de auditoría de un módulo de optimización adaptativa
STRUCT ModuleStatus {
    module_name: STRING;
    initialized: BOOL;
    last_operation: STRING;
    last_success: BOOL;
    error_message: STRING;
}

// Definición de error personalizada para módulos de optimización
ERROR OptimizationModuleError: {
    message: STRING;
    module: STRING;
    code: INT;
}

// Función para inicializar el sistema de optimización adaptativa
// Esta función verifica la configuración de cada módulo y proporciona trazabilidad detallada.
FUNC INITIALIZE_ADAPTIVE_OPTIMIZATION(): BOOL;

// Función para terminar el sistema de optimización adaptativa
// Cierra y libera todos los recursos de cada módulo, con manejo seguro de errores.
FUNC TERMINATE_ADAPTIVE_OPTIMIZATION(): BOOL;

// Función auxiliar para validar las configuraciones antes de inicializar cada módulo
// Esta función asegura que los módulos necesarios estén configurados correctamente antes de su inicialización.
FUNC VALIDATE_CONFIGURATIONS(): BOOL;

// Funciones de acceso a la auditoría y el estado de cada módulo de optimización
FUNC GET_MODULE_STATUS(module_name: STRING): ModuleStatus;
FUNC GET_ALL_MODULE_STATUSES(): LIST<ModuleStatus>;

#endif // ADAPTIVE_OPTIMIZATION_H
