#ifndef PYTHON_INTERFACE_ADVANCED_H
#define PYTHON_INTERFACE_ADVANCED_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>

/**
 * @brief Módulo `python_interface_advanced` - Interfaz avanzada para integración con Python.
 *
 * Este módulo permite a MC++ gestionar entornos de Python embebidos, cargar módulos, ejecutar funciones,
 * y pasar datos entre MC++ y Python. Cada entorno es independiente y puede configurarse de manera específica.
 */

// Estructura para representar un entorno Python embebido y su configuración
struct PythonEnvironment {
    std::string id;                       // Identificador único del entorno
    std::string interpreter_path;         // Ruta al intérprete de Python
    bool initialized;                     // Estado de inicialización del entorno
    std::vector<std::string> modules_loaded; // Módulos de Python cargados en el entorno
    int last_execution_timestamp;         // Marca de tiempo de la última ejecución

    // Constructor
    PythonEnvironment(const std::string& id, const std::string& interpreter_path)
        : id(id), interpreter_path(interpreter_path), initialized(false), last_execution_timestamp(0) {}
};

// Definiciones de tipos para compatibilidad
using Variant = std::string; // Cambiar según la implementación real de Variant en MC++
using VariantList = std::vector<Variant>;
using VariantMap = std::map<std::string, Variant>;

// Funciones para la gestión de entornos Python embebidos

/**
 * @brief Crea un entorno Python embebido.
 * @param id Identificador único del entorno.
 * @param interpreter_path Ruta al intérprete de Python.
 * @return true si el entorno se crea correctamente, false en caso contrario.
 */
bool CREATE_PYTHON_ENVIRONMENT(const std::string& id, const std::string& interpreter_path = "/usr/bin/python3");

/**
 * @brief Inicializa un entorno Python embebido.
 * @param id Identificador único del entorno.
 * @return true si se inicializa correctamente, false en caso contrario.
 */
bool INITIALIZE_PYTHON_ENVIRONMENT(const std::string& id);

/**
 * @brief Carga un módulo en el entorno Python embebido.
 * @param id Identificador único del entorno.
 * @param module_name Nombre del módulo de Python.
 * @return true si el módulo se carga correctamente, false en caso contrario.
 */
bool LOAD_PYTHON_MODULE(const std::string& id, const std::string& module_name);

/**
 * @brief Ejecuta una función de Python en el entorno embebido.
 * @param id Identificador único del entorno.
 * @param module_name Nombre del módulo de Python.
 * @param function_name Nombre de la función a ejecutar.
 * @param args Lista de argumentos para la función.
 * @param kwargs Mapa de argumentos con nombre para la función.
 * @return Resultado de la ejecución en formato Variant.
 */
Variant EXECUTE_PYTHON_FUNCTION(const std::string& id, const std::string& module_name, const std::string& function_name, const VariantList& args, const VariantMap& kwargs);

/**
 * @brief Pasa datos desde MC++ a Python como variables globales.
 * @param id Identificador único del entorno.
 * @param data Datos en formato Variant para transferir a Python.
 * @return true si los datos se transfieren correctamente, false en caso contrario.
 */
bool PASS_DATA_TO_PYTHON(const std::string& id, const Variant& data);

/**
 * @brief Recupera datos desde Python en formato MC++.
 * @param id Identificador único del entorno.
 * @param variable_name Nombre de la variable global en Python.
 * @return Datos recuperados en formato Variant.
 */
Variant RETRIEVE_DATA_FROM_PYTHON(const std::string& id, const std::string& variable_name);

/**
 * @brief Evalúa código Python en el entorno embebido.
 * @param id Identificador único del entorno.
 * @param code Código Python a evaluar.
 * @return Resultado de la evaluación en formato Variant.
 */
Variant EVALUATE_PYTHON_CODE(const std::string& id, const std::string& code);

/**
 * @brief Cierra y limpia un entorno Python embebido.
 * @param id Identificador único del entorno.
 * @return true si el entorno se cierra correctamente, false en caso contrario.
 */
bool CLOSE_PYTHON_ENVIRONMENT(const std::string& id);

/**
 * @brief Lista los entornos Python activos y sus módulos cargados.
 * @return Lista de mapas con información de los entornos activos.
 */
std::vector<VariantMap> LIST_ACTIVE_ENVIRONMENTS();

/**
 * @brief Verifica la integridad de un entorno Python embebido.
 * @param id Identificador único del entorno.
 * @return true si la integridad es correcta, false en caso contrario.
 */
bool VERIFY_ENVIRONMENT_INTEGRITY(const std::string& id);

/**
 * @brief Configura parámetros específicos del entorno Python.
 * @param id Identificador único del entorno.
 * @param config_key Clave del parámetro de configuración.
 * @param config_value Valor del parámetro de configuración.
 * @return true si la configuración se aplica correctamente, false en caso contrario.
 */
bool SET_PYTHON_CONFIG(const std::string& id, const std::string& config_key, const Variant& config_value);

#endif // PYTHON_INTERFACE_ADVANCED_H
