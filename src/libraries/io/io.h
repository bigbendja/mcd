#ifndef IO_H
#define IO_H

#include "file_management.h"     // Gestión avanzada de archivos
#include "user_input.h"          // Captura y validación de entrada de usuario
#include "output_formatting.h"   // Formateo y presentación de salida

/**
 * @file io.h
 * @brief Cabecera principal de la biblioteca de Entrada/Salida (IO) en MC++.
 * 
 * La biblioteca `io` proporciona herramientas avanzadas para la manipulación de archivos,
 * captura y validación de entrada de usuario, y formato de salida. Este archivo centraliza
 * la inclusión de módulos principales de IO para facilitar su acceso y uso en aplicaciones de alto rendimiento.
 * 
 * ## Módulos incluidos:
 * - `file_management.h`: Operaciones de manipulación y control de archivos.
 * - `user_input.h`: Herramientas de captura y validación de entrada.
 * - `output_formatting.h`: Funciones avanzadas de formateo y presentación.
 * 
 * ## Configuración Global (Ejemplo):
 * La biblioteca permite establecer configuraciones globales, como codificación de archivos o mensajes
 * predeterminados para la entrada y salida. Estas configuraciones se pueden definir en una función de 
 * inicialización opcional.
 */

/**
 * @brief Inicializa la biblioteca `io` con configuraciones globales.
 * 
 * Esta función es opcional y permite establecer parámetros globales, como:
 * - Codificación predeterminada para operaciones de archivos.
 * - Mensajes predeterminados para entrada de usuario.
 * - Opciones de formato para salida.
 * 
 * @param encoding Codificación predeterminada (ejemplo: "UTF-8").
 * @param default_date_format Formato de fecha predeterminado (ejemplo: "YYYY-MM-DD").
 * @return `true` si la inicialización es exitosa.
 */
bool IO_INIT(const std::string& encoding = "UTF-8", const std::string& default_date_format = "YYYY-MM-DD");

#endif // IO_H
