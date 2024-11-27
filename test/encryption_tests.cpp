#include "encryption.h"
#include <iostream>
#include <cassert>
#include <fstream>

// Helper para imprimir el resultado de una prueba
void PrintTestResult(const std::string& testName, bool result) {
    std::cout << testName << ": " << (result ? "PASSED" : "FAILED") << std::endl;
    assert(result);
}

// Prueba de generación de claves
void TestGenerateKey() {
    std::string key = GenerateKey(256); // 256 bits
    PrintTestResult("TestGenerateKey", key.size() == 64); // 256 bits -> 64 caracteres hexadecimales
}

// Prueba de encriptación y desencriptación AES
void TestAESEncryptionDecryption() {
    const std::string data = "Test data for encryption.";
    const std::string key = GenerateKey(256);
    const std::string iv = GenerateKey(128);

    std::string encrypted = AESEncrypt(data, key, iv);
    std::string decrypted = AESDecrypt(encrypted, key, iv);

    PrintTestResult("TestAESEncryptionDecryption", data == decrypted);
}

// Prueba de hashes SHA
void TestSHAHashing() {
    const std::string data = "Test data for hashing.";
    std::string hash256 = HashSHA256(data);
    std::string hash512 = HashSHA512(data);

    PrintTestResult("TestSHA256", hash256.size() == 64); // 256 bits -> 64 caracteres hexadecimales
    PrintTestResult("TestSHA512", hash512.size() == 128); // 512 bits -> 128 caracteres hexadecimales
}

// Prueba de derivación de claves PBKDF2
void TestPBKDF2() {
    const std::string password = "securepassword";
    const std::string salt = GenerateSalt(16);
    std::string derivedKey = PBKDF2DeriveKey(password, salt, 10000, 256); // Derivar clave de 256 bits

    PrintTestResult("TestPBKDF2", derivedKey.size() == 64); // 256 bits -> 64 caracteres hexadecimales
}

// Prueba de generación y validación de pares de claves RSA
void TestRSAGeneration() {
    auto [publicKey, privateKey] = RSAGenerateKeys(2048); // Par de claves RSA de 2048 bits

    PrintTestResult("TestRSAGeneration", !publicKey.empty() && !privateKey.empty());
}

// Prueba de manejo de archivos cifrados
void TestEncryptedFileHandling() {
    const std::string filename = "test_encrypted_file.txt";
    const std::string key = GenerateKey(256);
    const std::string iv = GenerateKey(128);
    const std::string data = "This is sensitive information.";

    // Escribir archivo cifrado
    {
        std::ofstream outFile(filename, std::ios::binary);
        std::string encrypted = AESEncrypt(data, key, iv);
        outFile << encrypted;
        outFile.close();
    }

    // Leer y descifrar archivo
    {
        std::ifstream inFile(filename, std::ios::binary);
        std::string encrypted((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        std::string decrypted = AESDecrypt(encrypted, key, iv);

        PrintTestResult("TestEncryptedFileHandling", data == decrypted);
    }

    // Limpieza
    std::remove(filename.c_str());
}

int main() {
    std::cout << "Iniciando pruebas para el módulo de cifrado." << std::endl;

    TestGenerateKey();
    TestAESEncryptionDecryption();
    TestSHAHashing();
    TestPBKDF2();
    TestRSAGeneration();
    TestEncryptedFileHandling();

    std::cout << "Todas las pruebas completadas exitosamente." << std::endl;
    return 0;
}
