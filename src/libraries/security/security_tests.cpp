#include "security.h"
#include <iostream>
#include <cassert>

void testEncryptionDecryption() {
    std::string originalText = "Confidential Data";
    std::string key = GenerateKey();

    std::string encryptedText = AESEncrypt(originalText, key);
    assert(!encryptedText.empty() && "Encryption failed - empty result.");

    std::string decryptedText = AESDecrypt(encryptedText, key);
    assert(decryptedText == originalText && "Decryption failed - data mismatch.");

    std::cout << "[PASSED] Encryption/Decryption test.\n";
}

void testHashIntegrity() {
    std::string data = "Sensitive Data";

    std::string hash1 = HashSHA256(data);
    std::string hash2 = HashSHA256(data);

    assert(hash1 == hash2 && "Hash integrity test failed - hashes do not match.");

    std::string tamperedData = data + "tampered";
    std::string tamperedHash = HashSHA256(tamperedData);

    assert(hash1 != tamperedHash && "Hash integrity test failed - tampered data hash matches original.");

    std::cout << "[PASSED] Hash integrity test.\n";
}

void testJWTGenerationAndValidation() {
    std::string user = "user123";
    std::string token = GenerateSessionToken(user, 3600);

    assert(!token.empty() && "JWT generation failed - empty token.");

    bool isValid = VerifySessionToken(token);
    assert(isValid && "JWT validation failed - token is invalid.");

    std::cout << "[PASSED] JWT generation and validation test.\n";
}

void testAccessControl() {
    assert(AssignRole("admin", "delete") && "Access control test failed - admin delete role not assigned.");
    assert(HasRole("admin", "delete") && "Access control test failed - admin delete role missing.");
    assert(!HasRole("guest", "write") && "Access control test failed - guest write access should be denied.");

    std::cout << "[PASSED] Access control test.\n";
}

void testAuditLogging() {
    bool result = RecordAccess("security_tests", "Testing audit logging.", true);
    assert(result && "Audit logging test failed - unable to log event.");

    std::cout << "[PASSED] Audit logging test.\n";
}

void testKeyManagement() {
    std::string masterKey = GenerateMasterKey();
    std::string sessionKey = GenerateSessionKey("session123", 256);

    assert(!masterKey.empty() && "Master key generation failed.");
    assert(!sessionKey.empty() && "Session key generation failed.");

    bool stored = StoreKey("key1", sessionKey, masterKey);
    assert(stored && "Key management test failed - unable to store key.");

    std::string retrievedKey = RetrieveKey("key1", masterKey);
    assert(retrievedKey == sessionKey && "Key management test failed - retrieved key mismatch.");

    bool deleted = DeleteKey("key1");
    assert(deleted && "Key management test failed - unable to delete key.");

    std::cout << "[PASSED] Key management test.\n";
}

int main() {
    std::cout << "Running security tests...\n";
    testEncryptionDecryption();
    testHashIntegrity();
    testJWTGenerationAndValidation();
    testAccessControl();
    testAuditLogging();
    testKeyManagement();
    std::cout << "All security tests passed.\n";
    return 0;
}
