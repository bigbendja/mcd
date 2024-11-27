#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <future>

/**
 * Manejador de archivos seguro y avanzado.
 * Define funciones para gestionar operaciones de E/S de archivos en MC++.
 */

using FILE_HANDLE = std::shared_ptr<std::fstream>;

// -------------------------------------
// Operaciones básicas de archivo
// -------------------------------------

/**
 * Abre un archivo en el modo especificado.
 * 
 * @param path Ruta del archivo.
 * @param mode Modo de apertura: "r" para lectura, "w" para escritura, "a" para agregar.
 * @return FILE_HANDLE al archivo abierto.
 * @throws std::invalid_argument si el modo es inválido.
 * @throws std::runtime_error si el archivo no se puede abrir.
 */
FILE_HANDLE OPEN_FILE(const std::string& path, const std::string& mode);

/**
 * Cierra el archivo y libera los recursos asociados.
 * 
 * @param file FILE_HANDLE al archivo.
 * @return true si se cierra correctamente, false en caso contrario.
 */
bool CLOSE_FILE(FILE_HANDLE file);

// -------------------------------------
// Operaciones de lectura y escritura
// -------------------------------------

/**
 * Lee el contenido del archivo.
 * 
 * @param file FILE_HANDLE al archivo.
 * @param num_bytes Número de bytes a leer (-1 para leer todo el contenido).
 * @return Cadena con el contenido leído.
 * @throws std::runtime_error si el archivo no está en modo lectura.
 */
std::string READ_FILE(FILE_HANDLE file, int num_bytes = -1);

/**
 * Lee el contenido del archivo de manera asíncrona.
 * 
 * @param file FILE_HANDLE al archivo.
 * @param num_bytes Número de bytes a leer (-1 para leer todo el contenido).
 * @return std::future con el contenido leído.
 */
std::future<std::string> READ_FILE_ASYNC(FILE_HANDLE file, int num_bytes = -1);

/**
 * Escribe datos en el archivo.
 * 
 * @param file FILE_HANDLE al archivo.
 * @param data Cadena de datos a escribir.
 * @return true si la operación de escritura es exitosa.
 * @throws std::runtime_error si el archivo no está en modo escritura.
 */
bool WRITE_FILE(FILE_HANDLE file, const std::string& data);

/**
 * Escribe datos en el archivo de manera asíncrona.
 * 
 * @param file FILE_HANDLE al archivo.
 * @param data Cadena de datos a escribir.
 * @return std::future<bool> indicando si la operación fue exitosa.
 */
std::future<bool> WRITE_FILE_ASYNC(FILE_HANDLE file, const std::string& data);

/**
 * Lee todas las líneas del archivo en un vector de cadenas.
 * 
 * @param file FILE_HANDLE al archivo.
 * @return Vector de cadenas con cada línea del archivo.
 * @throws std::runtime_error si el archivo no está en modo lectura.
 */
std::vector<std::string> READ_LINES(FILE_HANDLE file);

/**
 * Escribe múltiples líneas en el archivo.
 * 
 * @param file FILE_HANDLE al archivo.
 * @param lines Vector de cadenas, cada una representa una línea.
 * @return true si la escritura es exitosa.
 * @throws std::runtime_error si el archivo no está en modo escritura.
 */
bool WRITE_LINES(FILE_HANDLE file, const std::vector<std::string>& lines);

// -------------------------------------
// Operaciones de gestión de archivos
// -------------------------------------

/**
 * Agrega datos al final del archivo.
 * 
 * @param path Ruta del archivo.
 * @param data Cadena de datos a agregar.
 * @return true si la operación de agregado es exitosa.
 * @throws std::runtime_error si el archivo no se puede abrir.
 */
bool APPEND_FILE(const std::string& path, const std::string& data);

/**
 * Elimina el archivo especificado.
 * 
 * @param path Ruta del archivo.
 * @return true si el archivo es eliminado exitosamente.
 */
bool DELETE_FILE(const std::string& path);

/**
 * Verifica si el archivo existe.
 * 
 * @param path Ruta del archivo.
 * @return true si el archivo existe, false en caso contrario.
 */
bool FILE_EXISTS(const std::string& path);

/**
 * Copia un archivo a una nueva ubicación.
 * 
 * @param source_path Ruta del archivo origen.
 * @param destination_path Ruta de destino.
 * @return true si la copia es exitosa.
 * @throws std::filesystem::filesystem_error si ocurre un error en la copia.
 */
bool COPY_FILE(const std::string& source_path, const std::string& destination_path);

/**
 * Mueve un archivo a una nueva ubicación.
 * 
 * @param source_path Ruta del archivo origen.
 * @param destination_path Ruta de destino.
 * @return true si el movimiento es exitoso.
 */
bool MOVE_FILE(const std::string& source_path, const std::string& destination_path);

// -------------------------------------
// Metadatos de archivos
// -------------------------------------

/**
 * Obtiene el tamaño del archivo en bytes.
 * 
 * @param file FILE_HANDLE al archivo.
 * @return Tamaño del archivo en bytes.
 * @throws std::runtime_error si el archivo no está abierto.
 */
int GET_FILE_SIZE(FILE_HANDLE file);

/**
 * Obtiene información detallada del archivo.
 * 
 * @param path Ruta del archivo.
 * @return Mapa con información sobre permisos, tamaño y tiempo de última modificación.
 * @throws std::runtime_error si el archivo no existe.
 */
std::map<std::string, std::string> GET_FILE_INFO(const std::string& path);

#endif // FILE_MANAGEMENT_H
