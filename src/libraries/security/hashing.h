#ifndef HASHING_H
#define HASHING_H

#include <string>

/**
 * @file hashing.h
 * @brief Módulo de hashing seguro y generación de HMACs para aplicaciones críticas.
 * 
 * Proporciona funciones para hashing seguro con SHA-256/SHA-512, generación de HMACs, 
 * y verificación de integridad de datos mediante comparación de hashes.
 */

/**
 * @brief Genera un hash seguro usando SHA-256.
 * @param data Datos de entrada para generar el hash.
 * @return Hash en formato hexadecimal.
 */
std::string HashSHA256(const std::string& data);

/**
 * @brief Genera un hash seguro usando SHA-512.
 * @param data Datos de entrada para generar el hash.
 * @return Hash en formato hexadecimal.
 */
std::string HashSHA512(const std::string& data);

/**
 * @brief Genera un HMAC usando SHA-256 y una clave secreta.
 * @param data Datos de entrada para el HMAC.
 * @param key Clave secreta utilizada para generar el HMAC.
 * @return HMAC en formato hexadecimal.
 */
std::string HMACSHA256(const std::string& data, const std::string& key);

/**
 * @brief Genera un HMAC usando SHA-512 y una clave secreta.
 * @param data Datos de entrada para el HMAC.
 * @param key Clave secreta utilizada para generar el HMAC.
 * @return HMAC en formato hexadecimal.
 */
std::string HMACSHA512(const std::string& data, const std::string& key);

/**
 * @brief Verifica si un hash dado coincide con el hash calculado para los datos.
 * @param data Datos originales para verificar el hash.
 * @param hash Hash proporcionado para comparar.
 * @param algorithm Algoritmo de hashing usado (valores soportados: "SHA256", "SHA512").
 * @return Verdadero si los hashes coinciden, falso en caso contrario.
 * @throws std::invalid_argument si el algoritmo no es soportado.
 */
bool VerifyHash(const std::string& data, const std::string& hash, const std::string& algorithm = "SHA256");

#endif // HASHING_H
