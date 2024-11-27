#include "key_management.h"
#include "encryption.h"
#include <stdexcept>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>

// Espacio de almacenamiento seguro simulado
static std::map<std::string, std::string> SecureStorage;

/**
 * @brief Genera una cantidad de bytes aleatorios seguros.
 * @param length Cantidad de bytes a generar.
 * @return Cadena binaria con los bytes generados.
 */
std::string GenerateRandomBytes(int length) {
    std::vector<unsigned char> buffer(length);
    if (!RAND_bytes(buffer.data(), length)) {
        throw std::runtime_error("Error al generar bytes aleatorios");
    }
    return std::string(buffer.begin(), buffer.end());
}

std::string GenerateMasterKey(int key_length) {
    return GenerateRandomBytes(key_length / 8);
}

std::string DeriveKey(const std::string& master_key, const std::string& salt, int iterations, int key_length) {
    std::vector<unsigned char> derived_key(key_length / 8);
    if (!PKCS5_PBKDF2_HMAC(master_key.c_str(), master_key.size(),
                           reinterpret_cast<const unsigned char*>(salt.c_str()), salt.size(),
                           iterations, EVP_sha256(), derived_key.size(), derived_key.data())) {
        throw std::runtime_error("Error al derivar clave con PBKDF2");
    }
    return std::string(derived_key.begin(), derived_key.end());
}

std::string GenerateSessionKey(const std::string& session_id, int key_length) {
    std::string salt = GenerateRandomBytes(16);
    return DeriveKey(session_id, salt, 10000, key_length);
}

bool StoreKey(const std::string& key_id, const std::string& key_data, const std::string& master_key) {
    std::string encrypted_key = AESEncrypt(key_data, master_key, GenerateRandomBytes(16));
    SecureStorage[key_id] = encrypted_key;
    return true;
}

std::string RetrieveKey(const std::string& key_id, const std::string& master_key) {
    auto it = SecureStorage.find(key_id);
    if (it == SecureStorage.end()) {
        throw std::runtime_error("Clave no encontrada en el almacenamiento seguro");
    }
    return AESDecrypt(it->second, master_key, GenerateRandomBytes(16));
}

bool DeleteKey(const std::string& key_id) {
    auto it = SecureStorage.find(key_id);
    if (it != SecureStorage.end()) {
        SecureStorage.erase(it);
        return true;
    }
    return false;
}

bool VerifyKeyIntegrity(const std::string& key_data, const std::string& hash_value, const std::string& algorithm) {
    std::string computed_hash = (algorithm == "SHA256") ? HashSHA256(key_data) :
                                (algorithm == "SHA512") ? HashSHA512(key_data) :
                                throw std::invalid_argument("Algoritmo de hash no soportado");
    return computed_hash == hash_value;
}

bool RotateKey(const std::string& key_id, const std::string& new_key_data, const std::string& master_key) {
    return StoreKey(key_id, new_key_data, master_key);
}

std::string ExportKey(const std::string& key_id, const std::string& master_key, const std::string& export_format) {
    std::string key_data = RetrieveKey(key_id, master_key);
    if (export_format == "BASE64") {
        return Base64Encode(key_data);
    } else if (export_format == "HEX") {
        std::ostringstream oss;
        for (unsigned char ch : key_data) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ch);
        }
        return oss.str();
    } else {
        throw std::invalid_argument("Formato de exportación no soportado");
    }
}

bool ImportKey(const std::string& key_id, const std::string& imported_key, const std::string& master_key, const std::string& import_format) {
    std::string key_data;
    if (import_format == "BASE64") {
        key_data = Base64Decode(imported_key);
    } else if (import_format == "HEX") {
        std::istringstream iss(imported_key);
        key_data.resize(imported_key.size() / 2);
        for (auto& ch : key_data) {
            unsigned int byte;
            iss >> std::hex >> byte;
            ch = static_cast<unsigned char>(byte);
        }
    } else {
        throw std::invalid_argument("Formato de importación no soportado");
    }
    return StoreKey(key_id, key_data, master_key);
}

std::string GenerateSalt(int length) {
    return GenerateRandomBytes(length);
}
