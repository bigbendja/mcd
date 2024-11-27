#ifndef KEY_MANAGEMENT_H
#define KEY_MANAGEMENT_H

#include <string>

/**
 * @file key_management.h
 * @brief Proporciona funciones avanzadas para la generación, almacenamiento y gestión de claves criptográficas.
 *        Este módulo está diseñado para garantizar seguridad y flexibilidad en la gestión de claves.
 */

// ------------------- Generación y Derivación de Claves -------------------

/**
 * @brief Genera una clave maestra segura de longitud especificada en bits.
 * @param key_length Longitud de la clave en bits (por defecto, 256 bits).
 * @return Cadena binaria que representa la clave maestra generada.
 */
std::string GenerateMasterKey(int key_length = 256);

/**
 * @brief Deriva una clave a partir de una clave maestra usando PBKDF2.
 * @param master_key Clave maestra de entrada.
 * @param salt Valor de sal único.
 * @param iterations Número de iteraciones para la derivación (por defecto, 10,000).
 * @param key_length Longitud deseada de la clave derivada en bits (por defecto, 256 bits).
 * @return Clave derivada como una cadena binaria.
 */
std::string DeriveKey(const std::string& master_key, const std::string& salt, int iterations = 10000, int key_length = 256);

/**
 * @brief Genera una clave de sesión segura basada en un identificador único.
 * @param session_id Identificador único de la sesión.
 * @param key_length Longitud deseada de la clave en bits (por defecto, 256 bits).
 * @return Clave de sesión como una cadena binaria.
 */
std::string GenerateSessionKey(const std::string& session_id, int key_length = 256);

// ------------------- Almacenamiento y Recuperación de Claves -------------------

/**
 * @brief Almacena una clave de manera segura cifrándola con una clave maestra.
 * @param key_id Identificador único de la clave a almacenar.
 * @param key_data Datos de la clave en formato binario.
 * @param master_key Clave maestra usada para cifrar la clave.
 * @return `true` si la clave se almacenó correctamente, `false` en caso contrario.
 */
bool StoreKey(const std::string& key_id, const std::string& key_data, const std::string& master_key);

/**
 * @brief Recupera una clave cifrada del almacenamiento seguro.
 * @param key_id Identificador único de la clave a recuperar.
 * @param master_key Clave maestra usada para descifrar la clave.
 * @return Datos de la clave en formato binario.
 * @throws std::runtime_error si la clave no existe en el almacenamiento.
 */
std::string RetrieveKey(const std::string& key_id, const std::string& master_key);

/**
 * @brief Elimina de forma segura una clave del almacenamiento.
 * @param key_id Identificador único de la clave a eliminar.
 * @return `true` si la clave se eliminó correctamente, `false` si no se encontró.
 */
bool DeleteKey(const std::string& key_id);

// ------------------- Integridad y Rotación de Claves -------------------

/**
 * @brief Verifica la integridad de una clave mediante un hash.
 * @param key_data Datos de la clave en formato binario.
 * @param hash_value Valor de hash almacenado.
 * @param algorithm Algoritmo de hash usado (por defecto, "SHA256").
 * @return `true` si el hash calculado coincide con el hash almacenado, `false` en caso contrario.
 * @throws std::invalid_argument si el algoritmo no es soportado.
 */
bool VerifyKeyIntegrity(const std::string& key_data, const std::string& hash_value, const std::string& algorithm = "SHA256");

/**
 * @brief Rota una clave reemplazándola por una nueva en el almacenamiento seguro.
 * @param key_id Identificador único de la clave a rotar.
 * @param new_key_data Datos de la nueva clave en formato binario.
 * @param master_key Clave maestra usada para cifrar la nueva clave.
 * @return `true` si la clave se rotó correctamente, `false` en caso contrario.
 */
bool RotateKey(const std::string& key_id, const std::string& new_key_data, const std::string& master_key);

// ------------------- Exportación e Importación de Claves -------------------

/**
 * @brief Exporta una clave en un formato seguro (Base64 o Hexadecimal).
 * @param key_id Identificador único de la clave a exportar.
 * @param master_key Clave maestra usada para descifrar la clave antes de exportarla.
 * @param export_format Formato deseado para la exportación ("BASE64" o "HEX").
 * @return Clave exportada en el formato especificado.
 * @throws std::invalid_argument si el formato no es soportado.
 */
std::string ExportKey(const std::string& key_id, const std::string& master_key, const std::string& export_format = "BASE64");

/**
 * @brief Importa una clave desde un formato seguro (Base64 o Hexadecimal) y la almacena en el sistema.
 * @param key_id Identificador único para la clave importada.
 * @param imported_key Clave importada en formato especificado.
 * @param master_key Clave maestra usada para cifrar la clave antes de almacenarla.
 * @param import_format Formato de la clave importada ("BASE64" o "HEX").
 * @return `true` si la clave se importó y almacenó correctamente, `false` en caso contrario.
 * @throws std::invalid_argument si el formato no es soportado.
 */
bool ImportKey(const std::string& key_id, const std::string& imported_key, const std::string& master_key, const std::string& import_format = "BASE64");

// ------------------- Generación de Sal -------------------

/**
 * @brief Genera una sal aleatoria para derivación de claves.
 * @param length Longitud de la sal en bytes (por defecto, 16 bytes).
 * @return Cadena binaria que representa la sal generada.
 */
std::string GenerateSalt(int length = 16);

#endif // KEY_MANAGEMENT_H
