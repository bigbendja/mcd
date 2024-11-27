#include "authentication.h"
#include "audit_manager.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>

// Configuración para pruebas
const int MAX_LOGIN_ATTEMPTS = 5; // Asegúrate de que coincide con security_config.json
const int BLOCK_DURATION_SECONDS = 60;

// Simulación de intentos de inicio de sesión fallidos
void simulateFailedLogins(const std::string& username) {
    for (int i = 0; i < MAX_LOGIN_ATTEMPTS; i++) {
        bool success = AuthenticateUser(username, "wrong_password");
        assert(!success && "Error: La autenticación debería fallar.");
    }
    std::cout << "Simulación completada: Intentos fallidos para usuario " << username << std::endl;
}

// Validar que un usuario se bloquea tras superar los intentos máximos
void testUserBlockage() {
    std::string testUser = "test_user";
    RegisterUser(testUser, "correct_password", {});

    simulateFailedLogins(testUser);

    bool success = AuthenticateUser(testUser, "correct_password");
    assert(!success && "Error: El usuario debería estar bloqueado.");
    std::cout << "Prueba de bloqueo de usuario: PASADA." << std::endl;
}

// Validar desbloqueo tras el periodo de cooldown
void testCooldownMechanism() {
    std::string testUser = "cooldown_user";
    RegisterUser(testUser, "correct_password", {});

    simulateFailedLogins(testUser);

    std::this_thread::sleep_for(std::chrono::seconds(BLOCK_DURATION_SECONDS + 5));

    bool success = AuthenticateUser(testUser, "correct_password");
    assert(success && "Error: El usuario debería estar desbloqueado después del cooldown.");
    std::cout << "Prueba de mecanismo de cooldown: PASADA." << std::endl;
}

int main() {
    std::cout << "Iniciando pruebas de estrés para 'authentication'." << std::endl;

    testUserBlockage();
    testCooldownMechanism();

    std::cout << "Todas las pruebas de estrés completadas exitosamente." << std::endl;
    return 0;
}
