#ifndef SECURITY_H
#define SECURITY_H

#include <string>
#include <map>

/**
 * @file security.h
 * @brief Biblioteca principal de seguridad que agrupa funciones de generación de claves, cifrado, descifrado,
 *        hashing seguro, autenticación de mensajes y gestión de claves.
 */

// ------------------- Generación y Derivación de Claves -------------------

/**
 * @brief Genera una clave aleatoria segura de la longitud especificada.
 * @param key_length Longitud de la clave en bits (por defecto, 256 bits).
 * @return Cadena que representa la clave generada.
 */
std::string GenerateKey(int key_length = 256);

/**
 * @brief Deriva una clave segura a partir de una contraseña y una sal utilizando PBKDF2.
 * @param password Contraseña base para la derivación.
 * @param salt Sal utilizada para la derivación.
 * @param iterations Número de iteraciones para PBKDF2 (por defecto, 10,000).
 * @param key_length Longitud de la clave generada en bits (por defecto, 256 bits).
 * @return Cadena que representa la clave derivada.
 */
std::string PBKDF2DeriveKey(const std::string& password, const std::string& salt, int iterations = 10000, int key_length = 256);

/**
 * @brief Genera una sal aleatoria.
 * @param length Longitud de la sal en bytes (por defecto, 16 bytes).
 * @return Cadena que representa la sal generada.
 */
std::string GenerateSalt(int length = 16);

// ------------------- Cifrado y Descifrado AES -------------------

/**
 * @brief Cifra datos usando AES en modo CBC con una clave de 256 bits.
 * @param data Datos a cifrar.
 * @param key Clave de 256 bits utilizada para el cifrado.
 * @param iv Vector de inicialización (IV); si no se proporciona, se genera automáticamente.
 * @return Datos cifrados en formato binario.
 */
std::string AESEncrypt(const std::string& data, const std::string& key, const std::string& iv = "");

/**
 * @brief Descifra datos cifrados con AES en modo CBC.
 * @param encrypted_data Datos cifrados en formato binario.
 * @param key Clave de 256 bits utilizada para el descifrado.
 * @return Datos descifrados en formato original.
 */
std::string AESDecrypt(const std::string& encrypted_data, const std::string& key);

// ------------------- Cifrado y Descifrado RSA -------------------

/**
 * @brief Genera un par de claves RSA (pública y privada) con una longitud especificada.
 * @param key_size Longitud de las claves en bits (por defecto, 2048 bits).
 * @return Mapa que contiene las claves "public_key" y "private_key".
 */
std::map<std::string, std::string> RSAGenerateKeys(int key_size = 2048);

/**
 * @brief Cifra datos utilizando una clave pública RSA.
 * @param data Datos a cifrar.
 * @param public_key Clave pública utilizada para el cifrado.
 * @return Datos cifrados en formato binario.
 */
std::string RSAEncrypt(const std::string& data, const std::string& public_key);

/**
 * @brief Descifra datos utilizando una clave privada RSA.
 * @param encrypted_data Datos cifrados en formato binario.
 * @param private_key Clave privada utilizada para el descifrado.
 * @return Datos descifrados en formato original.
 */
std::string RSADecrypt(const std::string& encrypted_data, const std::string& private_key);

// ------------------- Funciones de Hashing Seguro -------------------

/**
 * @brief Genera un hash SHA-256 de los datos proporcionados.
 * @param data Datos a procesar.
 * @return Hash en formato hexadecimal.
 */
std::string HashSHA256(const std::string& data);

/**
 * @brief Genera un hash SHA-512 de los datos proporcionados.
 * @param data Datos a procesar.
 * @return Hash en formato hexadecimal.
 */
std::string HashSHA512(const std::string& data);

/**
 * @brief Verifica si el hash calculado coincide con un hash proporcionado.
 * @param data Datos originales.
 * @param hash Hash a verificar.
 * @param algorithm Algoritmo de hashing utilizado (por defecto, "SHA256").
 * @return `true` si el hash coincide, `false` en caso contrario.
 * @throws std::invalid_argument si el algoritmo no es soportado.
 */
bool VerifyHash(const std::string& data, const std::string& hash, const std::string& algorithm = "SHA256");

// ------------------- Código de Autenticación de Mensajes HMAC -------------------

/**
 * @brief Genera un HMAC-SHA256 para autenticación de mensajes.
 * @param data Datos a procesar.
 * @param key Clave secreta utilizada para generar el HMAC.
 * @return HMAC en formato hexadecimal.
 */
std::string HMACSHA256(const std::string& data, const std::string& key);

/**
 * @brief Genera un HMAC-SHA512 para autenticación de mensajes.
 * @param data Datos a procesar.
 * @param key Clave secreta utilizada para generar el HMAC.
 * @return HMAC en formato hexadecimal.
 */
std::string HMACSHA512(const std::string& data, const std::string& key);

// ------------------- Codificación y Decodificación Base64 -------------------

/**
 * @brief Codifica datos en formato Base64.
 * @param data Datos a codificar.
 * @return Cadena en formato Base64.
 */
std::string Base64Encode(const std::string& data);

/**
 * @brief Decodifica una cadena en formato Base64.
 * @param encoded_data Cadena codificada en Base64.
 * @return Datos decodificados en formato original.
 */
std::string Base64Decode(const std::string& encoded_data);

#endif // SECURITY_H
