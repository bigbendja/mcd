#include "security.h"
#include <cassert>
#include <iostream>

// Función auxiliar para ejecutar y mostrar resultados de pruebas unitarias
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas para cifrado y descifrado
void test_encryption_decryption() {
    std::string plain_text = "Texto de prueba para cifrado";
    std::string key = "clave_segura";
    std::string encrypted_text = security::encrypt(plain_text, key);
    std::string decrypted_text = security::decrypt(encrypted_text, key);

    run_test("Cifrado y descifrado", decrypted_text == plain_text);
}

// Pruebas para generación de hash seguro
void test_hash_generation() {
    std::string data = "Datos a hashear";
    std::string hash1 = security::generate_hash(data);
    std::string hash2 = security::generate_hash(data);

    run_test("Generación de hash consistente", hash1 == hash2);
    run_test("Verificación de hash único para datos diferentes", hash1 != security::generate_hash("Datos diferentes"));
}

// Pruebas de autenticación basada en token
void test_token_authentication() {
    std::string token = security::generate_auth_token("user_id_123");
    bool is_valid = security::validate_auth_token(token);

    run_test("Generación de token de autenticación", !token.empty());
    run_test("Validación de token de autenticación", is_valid);
}

// Pruebas de control de acceso
void test_access_control() {
    security::add_permission("user1", "READ");
    security::add_permission("user1", "WRITE");

    bool can_read = security::check_permission("user1", "READ");
    bool can_write = security::check_permission("user1", "WRITE");
    bool can_execute = security::check_permission("user1", "EXECUTE");

    run_test("Permiso de lectura", can_read);
    run_test("Permiso de escritura", can_write);
    run_test("Permiso de ejecución denegado", !can_execute);
}

// Prueba de auditoría y registro de eventos de seguridad
void test_security_audit() {
    bool audit_logged = security::log_security_event("TEST_EVENT", "Evento de prueba en auditoría", "INFO");

    run_test("Registro de evento de seguridad en auditoría", audit_logged);
}

// Pruebas de generación y validación de firmas digitales
void test_digital_signatures() {
    std::string data = "Datos a firmar";
    std::string private_key = security::generate_private_key();
    std::string signature = security::generate_signature(data, private_key);
    bool is_valid = security::validate_signature(data, signature, security::derive_public_key(private_key));

    run_test("Generación de firma digital", !signature.empty());
    run_test("Validación de firma digital", is_valid);
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'security'" << std::endl;

    test_encryption_decryption();
    test_hash_generation();
    test_token_authentication();
    test_access_control();
    test_security_audit();
    test_digital_signatures();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
