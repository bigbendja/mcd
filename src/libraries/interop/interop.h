#ifndef INTEROP_H
#define INTEROP_H

#include <string>
#include <variant>
#include <vector>
#include "python_interface_advanced.h"
#include "cpp_interface_advanced.h"
#include "rust_interface_advanced.h"
#include "data_conversion_advanced.h"

/**
 * Librería de Compatibilidad Multilenguaje Avanzada (`interop`) - MC++ 1.0
 * 
 * La librería `interop` permite la integración avanzada entre MC++ y otros lenguajes de programación 
 * como Python, C++ y Rust. Proporciona funciones para invocar funciones externas, manipular datos 
 * en diversos formatos y coordinar flujos de trabajo interlenguaje.
 */

// Alias para los tipos utilizados en funciones intermodulares
using VAR = std::variant<int, double, std::string, std::vector<std::string>, std::map<std::string, std::string>>;
using STRING = std::string;
using LIST = std::vector<VAR>;

// Funciones principales de la librería `interop`

/**
 * Llama a una función de un módulo Python cargado previamente.
 * @param module: Nombre del módulo de Python.
 * @param function: Nombre de la función a ejecutar.
 * @param args: Lista de argumentos para la función.
 * @return Resultado de la ejecución en formato VAR.
 */
VAR CALL_PYTHON_FUNCTION(const STRING& module, const STRING& function, const LIST& args);

/**
 * Ejecuta una función de una biblioteca C++ cargada.
 * @param library: Ruta o identificador de la biblioteca C++.
 * @param function: Nombre de la función a ejecutar.
 * @param args: Lista de argumentos para la función.
 * @return Resultado de la ejecución en formato VAR.
 */
VAR CALL_CPP_FUNCTION(const STRING& library, const STRING& function, const LIST& args);

/**
 * Llama a una función de una biblioteca Rust cargada.
 * @param library: Ruta o identificador de la biblioteca Rust.
 * @param function: Nombre de la función a ejecutar.
 * @param args: Lista de argumentos para la función.
 * @return Resultado de la ejecución en formato VAR.
 */
VAR CALL_RUST_FUNCTION(const STRING& library, const STRING& function, const LIST& args);

/**
 * Convierte un dato de MC++ a un formato compatible con lenguajes externos.
 * @param data: Datos en formato MC++.
 * @param lang: Lenguaje objetivo ("python", "cpp", "rust").
 * @return Datos convertidos en formato VAR.
 */
VAR CONVERT_TO_EXTERNAL_FORMAT(const VAR& data, const STRING& lang);

/**
 * Convierte un dato externo a formato MC++.
 * @param data: Datos en formato externo.
 * @return Datos convertidos a formato MC++.
 */
VAR CONVERT_TO_MC_FORMAT(const VAR& data);

/**
 * Configura parámetros específicos de un entorno embebido.
 * @param language: Lenguaje objetivo ("python", "cpp", "rust").
 * @param configKey: Clave del parámetro a configurar.
 * @param configValue: Valor del parámetro.
 * @return True si la configuración fue exitosa.
 */
bool SET_INTEROP_CONFIG(const STRING& language, const STRING& configKey, const VAR& configValue);

#endif // INTEROP_H
