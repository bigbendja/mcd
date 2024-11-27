#include "encryption.h"
#include <stdexcept>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

namespace {

std::string ToHex(const std::vector<unsigned char>& data) {
    std::ostringstream oss;
    for (const auto& byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}

void HandleOpenSSLError() {
    ERR_print_errors_fp(stderr);
    throw std::runtime_error("OpenSSL error occurred");
}

void SecureZeroMemory(void* ptr, size_t len) {
    volatile unsigned char* p = static_cast<unsigned char*>(ptr);
    while (len--) *p++ = 0;
}

} // namespace

std::string GenerateKey(int key_length) {
    if (key_length % 8 != 0) {
        throw std::invalid_argument("Key length must be a multiple of 8.");
    }

    std::vector<unsigned char> key(key_length / 8);
    if (!RAND_bytes(key.data(), key.size())) {
        HandleOpenSSLError();
    }

    return ToHex(key);
}

std::string AESEncrypt(const std::string& data, const std::string& key, const std::string& iv) {
    if (key.size() != 32 || iv.size() != 16) {
        throw std::invalid_argument("Key must be 256-bit (32 bytes) and IV must be 128-bit (16 bytes).");
    }

    std::vector<unsigned char> encryptedData(data.size() + AES_BLOCK_SIZE);
    int outLen1 = 0, outLen2 = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) HandleOpenSSLError();

    try {
        if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()))) {
            HandleOpenSSLError();
        }
        if (!EVP_EncryptUpdate(ctx, encryptedData.data(), &outLen1, reinterpret_cast<const unsigned char*>(data.data()), data.size())) {
            HandleOpenSSLError();
        }
        if (!EVP_EncryptFinal_ex(ctx, encryptedData.data() + outLen1, &outLen2)) {
            HandleOpenSSLError();
        }
    } catch (...) {
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }

    encryptedData.resize(outLen1 + outLen2);
    EVP_CIPHER_CTX_free(ctx);

    return ToHex(encryptedData);
}

std::string AESDecrypt(const std::string& encrypted_data, const std::string& key, const std::string& iv) {
    if (key.size() != 32 || iv.size() != 16) {
        throw std::invalid_argument("Key must be 256-bit (32 bytes) and IV must be 128-bit (16 bytes).");
    }

    std::vector<unsigned char> decryptedData(encrypted_data.size());
    int outLen1 = 0, outLen2 = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) HandleOpenSSLError();

    try {
        if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()))) {
            HandleOpenSSLError();
        }
        if (!EVP_DecryptUpdate(ctx, decryptedData.data(), &outLen1, reinterpret_cast<const unsigned char*>(encrypted_data.data()), encrypted_data.size())) {
            HandleOpenSSLError();
        }
        if (!EVP_DecryptFinal_ex(ctx, decryptedData.data() + outLen1, &outLen2)) {
            HandleOpenSSLError();
        }
    } catch (...) {
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }

    decryptedData.resize(outLen1 + outLen2);
    EVP_CIPHER_CTX_free(ctx);

    return std::string(decryptedData.begin(), decryptedData.end());
}

std::pair<std::string, std::string> RSAGenerateKeys(int key_size) {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    if (!BN_set_word(e, RSA_F4)) HandleOpenSSLError();

    if (!RSA_generate_key_ex(rsa, key_size, e, nullptr)) HandleOpenSSLError();

    BIO* pri = BIO_new(BIO_s_mem());
    BIO* pub = BIO_new(BIO_s_mem());

    if (!PEM_write_bio_RSAPrivateKey(pri, rsa, nullptr, nullptr, 0, nullptr, nullptr)) HandleOpenSSLError();
    if (!PEM_write_bio_RSAPublicKey(pub, rsa)) HandleOpenSSLError();

    char* priKey = nullptr;
    char* pubKey = nullptr;
    size_t priLen = BIO_get_mem_data(pri, &priKey);
    size_t pubLen = BIO_get_mem_data(pub, &pubKey);

    std::string privateKey(priKey, priLen);
    std::string publicKey(pubKey, pubLen);

    BIO_free_all(pub);
    BIO_free_all(pri);
    RSA_free(rsa);
    BN_free(e);

    return {publicKey, privateKey};
}

std::string HashSHA256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    SecureZeroMemory(hash, sizeof(hash));
    return ToHex(std::vector<unsigned char>(hash, hash + SHA256_DIGEST_LENGTH));
}

std::string HashSHA512(const std::string& data) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    SecureZeroMemory(hash, sizeof(hash));
    return ToHex(std::vector<unsigned char>(hash, hash + SHA512_DIGEST_LENGTH));
}

std::string PBKDF2DeriveKey(const std::string& password, const std::string& salt, int iterations, int key_length) {
    std::vector<unsigned char> derivedKey(key_length / 8);
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), reinterpret_cast<const unsigned char*>(salt.c_str()), salt.size(), iterations, EVP_sha256(), derivedKey.size(), derivedKey.data())) {
        HandleOpenSSLError();
    }

    SecureZeroMemory(derivedKey.data(), derivedKey.size());
    return ToHex(derivedKey);
}

std::string GenerateSalt(int length) {
    std::vector<unsigned char> salt(length);
    if (!RAND_bytes(salt.data(), salt.size())) {
        HandleOpenSSLError();
    }
    return ToHex(salt);
}

// New Methods: File Encryption and Decryption
void EncryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) throw std::runtime_error("Cannot open input file");

    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string encrypted = AESEncrypt(buffer.str(), key, iv);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) throw std::runtime_error("Cannot open output file");

    out << encrypted;
}

void DecryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) throw std::runtime_error("Cannot open input file");

    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string decrypted = AESDecrypt(buffer.str(), key, iv);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) throw std::runtime_error("Cannot open output file");

    out << decrypted;
}
