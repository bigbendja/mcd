#include "hashing.h"
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iomanip>
#include <unordered_map>

// ------------------- Funciones Auxiliares -------------------

/**
 * @brief Convierte un array de bytes a una cadena hexadecimal.
 * @param bytes Array de bytes.
 * @param length Longitud del array.
 * @return Representación hexadecimal de los bytes.
 */
std::string BytesToHex(const unsigned char* bytes, size_t length) {
    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
    }
    return oss.str();
}

/**
 * @brief Lanza una excepción con un mensaje de error específico.
 * @param error_message Mensaje de error.
 */
void ThrowUnsupportedAlgorithm(const std::string& error_message) {
    throw std::invalid_argument("Unsupported hash algorithm: " + error_message);
}

// ------------------- Implementaciones de Hash -------------------

/**
 * @brief Genera un hash SHA-256 de los datos proporcionados.
 * @param data Datos de entrada.
 * @return Hash en formato hexadecimal.
 */
std::string HashSHA256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    if (SHA256_Init(&sha256) != 1) throw std::runtime_error("SHA256 initialization failed");
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);
    return BytesToHex(hash, SHA256_DIGEST_LENGTH);
}

/**
 * @brief Genera un hash SHA-512 de los datos proporcionados.
 * @param data Datos de entrada.
 * @return Hash en formato hexadecimal.
 */
std::string HashSHA512(const std::string& data) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    if (SHA512_Init(&sha512) != 1) throw std::runtime_error("SHA512 initialization failed");
    SHA512_Update(&sha512, data.c_str(), data.size());
    SHA512_Final(hash, &sha512);
    return BytesToHex(hash, SHA512_DIGEST_LENGTH);
}

// ------------------- Implementaciones de HMAC -------------------

/**
 * @brief Genera un HMAC-SHA256 de los datos proporcionados utilizando una clave.
 * @param data Datos de entrada.
 * @param key Clave secreta para HMAC.
 * @return HMAC en formato hexadecimal.
 */
std::string HMACSHA256(const std::string& data, const std::string& key) {
    unsigned char hmac_result[SHA256_DIGEST_LENGTH];
    unsigned int len = 0;
    if (!HMAC(EVP_sha256(), key.c_str(), key.size(),
              reinterpret_cast<const unsigned char*>(data.c_str()), data.size(),
              hmac_result, &len)) {
        throw std::runtime_error("HMAC-SHA256 generation failed");
    }
    return BytesToHex(hmac_result, len);
}

/**
 * @brief Genera un HMAC-SHA512 de los datos proporcionados utilizando una clave.
 * @param data Datos de entrada.
 * @param key Clave secreta para HMAC.
 * @return HMAC en formato hexadecimal.
 */
std::string HMACSHA512(const std::string& data, const std::string& key) {
    unsigned char hmac_result[SHA512_DIGEST_LENGTH];
    unsigned int len = 0;
    if (!HMAC(EVP_sha512(), key.c_str(), key.size(),
              reinterpret_cast<const unsigned char*>(data.c_str()), data.size(),
              hmac_result, &len)) {
        throw std::runtime_error("HMAC-SHA512 generation failed");
    }
    return BytesToHex(hmac_result, len);
}

// ------------------- Verificación de Hash -------------------

/**
 * @brief Verifica si el hash proporcionado coincide con el hash calculado para los datos.
 * @param data Datos originales.
 * @param hash Hash proporcionado.
 * @param algorithm Algoritmo de hash ("SHA256" o "SHA512").
 * @return Verdadero si el hash coincide, falso en caso contrario.
 */
bool VerifyHash(const std::string& data, const std::string& hash, const std::string& algorithm) {
    static const std::unordered_map<std::string, std::function<std::string(const std::string&)>> hash_functions = {
        {"SHA256", HashSHA256},
        {"SHA512", HashSHA512},
    };

    auto it = hash_functions.find(algorithm);
    if (it == hash_functions.end()) {
        ThrowUnsupportedAlgorithm(algorithm);
    }
    return it->second(data) == hash;
}
