#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <map>

// ------------------- Generación de Claves -------------------
/**
 * @brief Genera una clave segura de la longitud especificada (en bits).
 * @param key_length Longitud de la clave en bits (por defecto, 256).
 * @return Una clave generada en formato hexadecimal.
 */
std::string GenerateKey(int key_length = 256);

// ------------------- Cifrado y Descifrado AES -------------------
/**
 * @brief Cifra datos utilizando AES-256 en modo CBC.
 * @param data Datos a cifrar.
 * @param key Clave de 256 bits en formato hexadecimal.
 * @param iv Vector de inicialización (IV) de 128 bits en formato hexadecimal (opcional).
 * @return Los datos cifrados en formato hexadecimal.
 * @throws std::invalid_argument Si la clave o el IV no tienen la longitud requerida.
 */
std::string AESEncrypt(const std::string& data, const std::string& key, const std::string& iv = "");

/**
 * @brief Descifra datos cifrados con AES-256 en modo CBC.
 * @param encrypted_data Datos cifrados en formato hexadecimal.
 * @param key Clave de 256 bits en formato hexadecimal.
 * @param iv Vector de inicialización (IV) de 128 bits en formato hexadecimal.
 * @return Los datos originales en formato de texto.
 * @throws std::invalid_argument Si la clave o el IV no tienen la longitud requerida.
 */
std::string AESDecrypt(const std::string& encrypted_data, const std::string& key, const std::string& iv);

// ------------------- Cifrado y Descifrado RSA -------------------
/**
 * @brief Genera un par de claves RSA (pública y privada).
 * @param key_size Longitud de las claves en bits (por defecto, 2048).
 * @return Un par de claves: "public_key" y "private_key".
 */
std::pair<std::string, std::string> RSAGenerateKeys(int key_size = 2048);

/**
 * @brief Cifra datos utilizando una clave pública RSA.
 * @param data Datos a cifrar.
 * @param public_key Clave pública en formato PEM.
 * @return Los datos cifrados en formato hexadecimal.
 */
std::string RSAEncrypt(const std::string& data, const std::string& public_key);

/**
 * @brief Descifra datos utilizando una clave privada RSA.
 * @param encrypted_data Datos cifrados en formato hexadecimal.
 * @param private_key Clave privada en formato PEM.
 * @return Los datos originales en formato de texto.
 */
std::string RSADecrypt(const std::string& encrypted_data, const std::string& private_key);

// ------------------- Hashing Seguro -------------------
/**
 * @brief Genera un hash SHA-256 de los datos proporcionados.
 * @param data Datos de entrada.
 * @return El hash en formato hexadecimal.
 */
std::string HashSHA256(const std::string& data);

/**
 * @brief Genera un hash SHA-512 de los datos proporcionados.
 * @param data Datos de entrada.
 * @return El hash en formato hexadecimal.
 */
std::string HashSHA512(const std::string& data);

// ------------------- Código de Autenticación de Mensajes HMAC -------------------
/**
 * @brief Genera un HMAC-SHA256 para autenticación de mensajes.
 * @param data Datos de entrada.
 * @param key Clave secreta para HMAC.
 * @return El HMAC generado en formato hexadecimal.
 */
std::string HMACSHA256(const std::string& data, const std::string& key);

/**
 * @brief Genera un HMAC-SHA512 para autenticación de mensajes.
 * @param data Datos de entrada.
 * @param key Clave secreta para HMAC.
 * @return El HMAC generado en formato hexadecimal.
 */
std::string HMACSHA512(const std::string& data, const std::string& key);

// ------------------- Codificación Base64 -------------------
/**
 * @brief Codifica datos en formato Base64.
 * @param data Datos de entrada.
 * @return Los datos codificados en Base64.
 */
std::string Base64Encode(const std::string& data);

/**
 * @brief Decodifica una cadena en formato Base64.
 * @param encoded_data Datos codificados en Base64.
 * @return Los datos originales en formato de texto.
 */
std::string Base64Decode(const std::string& encoded_data);

// ------------------- Verificación de Hash -------------------
/**
 * @brief Verifica si un hash coincide con los datos originales utilizando un algoritmo especificado.
 * @param data Datos originales.
 * @param hash Hash en formato hexadecimal.
 * @param algorithm Algoritmo de hash utilizado (por defecto, "SHA256").
 * @return Verdadero si el hash coincide, falso en caso contrario.
 * @throws std::invalid_argument Si el algoritmo no es compatible.
 */
bool VerifyHash(const std::string& data, const std::string& hash, const std::string& algorithm = "SHA256");

// ------------------- Derivación de Claves con PBKDF2 -------------------
/**
 * @brief Deriva una clave segura a partir de una contraseña y sal utilizando PBKDF2.
 * @param password Contraseña de entrada.
 * @param salt Sal en formato hexadecimal.
 * @param iterations Número de iteraciones de PBKDF2 (por defecto, 10,000).
 * @param key_length Longitud de la clave en bits (por defecto, 256).
 * @return La clave derivada en formato hexadecimal.
 */
std::string PBKDF2DeriveKey(const std::string& password, const std::string& salt, int iterations = 10000, int key_length = 256);

// ------------------- Generación de Sal Aleatoria -------------------
/**
 * @brief Genera una sal aleatoria de la longitud especificada.
 * @param length Longitud de la sal en bytes (por defecto, 16).
 * @return La sal generada en formato hexadecimal.
 */
std::string GenerateSalt(int length = 16);

#endif // ENCRYPTION_H
