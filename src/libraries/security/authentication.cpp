#include "authentication.h"
#include "encryption.h"
#include "key_management.h"
#include "audit_manager.h" // Importación necesaria para integración con el sistema de auditoría
#include <stdexcept>
#include <map>
#include <chrono>
#include <random>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <thread>
#include <json/json.h> // Librería JSON para persistencia

// Variables globales para almacenamiento seguro
std::map<std::string, std::string> UserStorage;
std::map<std::string, std::vector<std::string>> UserRoles;
std::unordered_map<std::string, UserState> UserStates; // Para gestión de intentos y bloqueos

const std::string USER_DB_FILE = "user_db.json";
const int DEFAULT_MAX_LOGIN_ATTEMPTS = 5;
const int DEFAULT_INITIAL_BLOCK_DURATION = 60; // En segundos
const int DEFAULT_COOLDOWN_INCREMENT = 30; // En segundos
const int DEFAULT_RESET_ATTEMPTS_DURATION = 15 * 60; // En segundos

// Configuraciones cargadas
int maxLoginAttempts = DEFAULT_MAX_LOGIN_ATTEMPTS;
int initialBlockDuration = DEFAULT_INITIAL_BLOCK_DURATION;
int cooldownIncrement = DEFAULT_COOLDOWN_INCREMENT;
int resetAttemptsDuration = DEFAULT_RESET_ATTEMPTS_DURATION;
std::string encryptionKey;
std::string encryptionIV;

// Cargar configuraciones desde security_config.json
void LoadSecurityConfig() {
    const std::string CONFIG_FILE = "security_config.json";
    if (!std::filesystem::exists(CONFIG_FILE)) {
        std::cout << "[WARNING] Archivo de configuración no encontrado: usando valores predeterminados." << std::endl;
        return;
    }

    std::ifstream infile(CONFIG_FILE);
    Json::Value root;
    infile >> root;

    maxLoginAttempts = root.get("max_login_attempts", DEFAULT_MAX_LOGIN_ATTEMPTS).asInt();
    initialBlockDuration = root.get("initial_block_duration_seconds", DEFAULT_INITIAL_BLOCK_DURATION).asInt();
    cooldownIncrement = root.get("cooldown_increment_seconds", DEFAULT_COOLDOWN_INCREMENT).asInt();
    resetAttemptsDuration = root.get("reset_attempts_duration_minutes", DEFAULT_RESET_ATTEMPTS_DURATION / 60).asInt() * 60;

    encryptionKey = root["audit"]["audit_trail_encryption"]["key"].asString();
    encryptionIV = root["audit"]["audit_trail_encryption"]["iv"].asString();

    if (encryptionKey.empty() || encryptionIV.empty()) {
        throw std::runtime_error("[ERROR] Claves de cifrado no configuradas en security_config.json.");
    }

    std::cout << "[INFO] Configuración de seguridad cargada desde " << CONFIG_FILE << std::endl;
    mc_security::AuditManager::logEvent("Configuración de seguridad cargada exitosamente.", mc_security::AuditManager::EventLevel::INFO);
}

// Helper function to generate a secure random token
std::string GenerateSecureToken(int length = 64) {
    static const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    std::string token;
    for (int i = 0; i < length; ++i) {
        token += charset[dist(engine)];
    }
    return token;
}

// Load users and roles from a persistent storage
void LoadUserDatabase() {
    if (!std::filesystem::exists(USER_DB_FILE)) return;
    std::ifstream infile(USER_DB_FILE);
    Json::Value root;
    infile >> root;
    for (const auto& user : root["users"]) {
        try {
            std::string encryptedRecord = user["record"].asString();
            std::string decryptedRecord = AESDecrypt(encryptedRecord, encryptionKey, encryptionIV);
            UserStorage[user["username"].asString()] = decryptedRecord;

            for (const auto& role : user["roles"]) {
                UserRoles[user["username"].asString()].push_back(role.asString());
            }
        } catch (const std::exception& e) {
            mc_security::AuditManager::logEvent("Error descifrando datos de usuario: " + std::string(e.what()), mc_security::AuditManager::EventLevel::CRITICAL);
        }
    }
}

// Save users and roles to persistent storage
void SaveUserDatabase() {
    Json::Value root;
    for (const auto& [username, record] : UserStorage) {
        try {
            std::string encryptedRecord = AESEncrypt(record, encryptionKey, encryptionIV);
            Json::Value user;
            user["username"] = username;
            user["record"] = encryptedRecord;

            for (const auto& role : UserRoles[username]) {
                user["roles"].append(role);
            }
            root["users"].append(user);
        } catch (const std::exception& e) {
            mc_security::AuditManager::logEvent("Error cifrando datos de usuario: " + std::string(e.what()), mc_security::AuditManager::EventLevel::CRITICAL);
        }
    }
    std::ofstream outfile(USER_DB_FILE);
    outfile << root;
}

// Reset failed login attempts for a user
void ResetFailedAttempts(const std::string& username) {
    UserStates[username].failedAttempts = 0;
    UserStates[username].isBlocked = false;
}

// Apply cooldown for a user after exceeding maximum login attempts
void ApplyCooldown(const std::string& username) {
    int attempts = UserStates[username].failedAttempts;
    int blockDuration = initialBlockDuration + cooldownIncrement * (attempts - maxLoginAttempts);
    UserStates[username].blockEndTime = std::chrono::system_clock::now() + std::chrono::seconds(blockDuration);
    UserStates[username].isBlocked = true;
    mc_security::AuditManager::logEvent("Usuario bloqueado temporalmente: " + username, mc_security::AuditManager::EventLevel::CRITICAL);
}

// Registrar intentos fallidos en el sistema de auditoría
void LogFailedAttempt(const std::string& username) {
    mc_security::AuditManager::logEvent("Intento de acceso fallido para el usuario: " + username, mc_security::AuditManager::EventLevel::WARNING);
}

// Authenticate a user by verifying the stored hashed password
bool AuthenticateUser(const std::string& username, const std::string& password) {
    auto& userState = UserStates[username];

    // Check if the user is blocked
    if (userState.isBlocked) {
        if (std::chrono::system_clock::now() < userState.blockEndTime) {
            std::cout << "Usuario bloqueado. Intente nuevamente después de: "
                      << std::chrono::duration_cast<std::chrono::seconds>(userState.blockEndTime - std::chrono::system_clock::now()).count()
                      << " segundos." << std::endl;
            LogFailedAttempt(username);
            return false;
        } else {
            ResetFailedAttempts(username);
        }
    }

    auto it = UserStorage.find(username);
    if (it == UserStorage.end()) {
        LogFailedAttempt(username);
        return false;
    }

    std::string user_record = AESDecrypt(it->second, encryptionKey, encryptionIV);
    size_t delimiter_pos = user_record.find(':');
    std::string stored_hash = user_record.substr(0, delimiter_pos);
    std::string salt = user_record.substr(delimiter_pos + 1);

    std::string input_hash = PBKDF2DeriveKey(password, salt, 10000, 256);
    if (input_hash == stored_hash) {
        ResetFailedAttempts(username);
        std::cout << "Inicio de sesión exitoso para usuario: " << username << std::endl;
        mc_security::AuditManager::logEvent("Inicio de sesión exitoso para el usuario: " + username, mc_security::AuditManager::EventLevel::INFO);
        return true;
    }

    // Increment failed attempts and apply cooldown if necessary
    userState.failedAttempts++;
    LogFailedAttempt(username);

    if (userState.failedAttempts >= maxLoginAttempts) {
        ApplyCooldown(username);
        std::cout << "Usuario bloqueado temporalmente debido a múltiples intentos fallidos." << std::endl;
    } else {
        std::cout << "Contraseña incorrecta. Intentos restantes: "
                  << maxLoginAttempts - userState.failedAttempts << std::endl;
    }
    return false;
}
