#include "audit_manager.h"
#include <iostream>
#include <cassert>
#include <thread>
#include <fstream>

// Función de prueba para registrar y verificar eventos
void testLogEvent() {
    using namespace mc_security;

    // Limpieza inicial de eventos para la prueba
    AuditManager::logEvent("Inicio de sesión exitoso.", AuditManager::EventLevel::INFO);
    AuditManager::logEvent("Intento de acceso no autorizado.", AuditManager::EventLevel::WARNING);
    AuditManager::logEvent("Modificación no autorizada en configuración.", AuditManager::EventLevel::CRITICAL);

    // Verificar que el registro ha capturado eventos críticos correctamente
    auto criticalEvents = AuditManager::getCriticalEvents();
    assert(!criticalEvents.empty() && "Error: No se encontraron eventos críticos registrados.");
    std::cout << "Prueba de registro de eventos críticos: PASADA." << std::endl;
}

// Función de prueba para verificar la detección de patrones anómalos
void testAnalyzePatterns() {
    using namespace mc_security;

    // Añadir eventos críticos consecutivos para activar la alerta
    AuditManager::logEvent("Intento de acceso no autorizado.", AuditManager::EventLevel::CRITICAL);
    AuditManager::logEvent("Intento de acceso no autorizado repetido.", AuditManager::EventLevel::CRITICAL);
    AuditManager::logEvent("Intento de acceso no autorizado detectado nuevamente.", AuditManager::EventLevel::CRITICAL);
    AuditManager::logEvent("Nueva alerta crítica.", AuditManager::EventLevel::CRITICAL);

    // Llamada al análisis de patrones
    AuditManager::analyzePatterns();

    std::cout << "Prueba de análisis de patrones: COMPLETADA (verificar alerta en consola)." << std::endl;
}

// Función de prueba para asegurar la consistencia en el acceso concurrente
void testConcurrentLogging() {
    using namespace mc_security;

    // Registrar eventos desde diferentes hilos para verificar consistencia
    std::thread t1([]() { AuditManager::logEvent("Acceso concurrente 1", AuditManager::EventLevel::INFO); });
    std::thread t2([]() { AuditManager::logEvent("Acceso concurrente 2", AuditManager::EventLevel::WARNING); });
    std::thread t3([]() { AuditManager::logEvent("Acceso concurrente 3", AuditManager::EventLevel::CRITICAL); });

    t1.join();
    t2.join();
    t3.join();

    // Verificar que los eventos se registren sin errores de concurrencia
    auto criticalEvents = AuditManager::getCriticalEvents();
    assert(!criticalEvents.empty() && "Error: Evento crítico no registrado en acceso concurrente.");
    std::cout << "Prueba de consistencia en acceso concurrente: PASADA." << std::endl;
}

// Función de prueba para revisar logs cifrados y descifrados
void testEncryptedLogs() {
    using namespace mc_security;

    const std::string testLogFile = "test_log_file.txt";
    AuditManager::setLogFile(testLogFile);

    // Registrar eventos
    AuditManager::logEvent("Evento de prueba para cifrado.", AuditManager::EventLevel::INFO);
    AuditManager::logEvent("Evento crítico para cifrado.", AuditManager::EventLevel::CRITICAL);

    // Revisar logs descifrados
    std::cout << "Revisando logs descifrados..." << std::endl;
    AuditManager::viewAuditLogs();

    // Verificar si el archivo contiene logs
    std::ifstream logFile(testLogFile);
    assert(logFile.is_open() && "Error: El archivo de log no pudo ser abierto.");
    logFile.close();
    std::cout << "Prueba de logs cifrados/descifrados: PASADA." << std::endl;
}

// Función de prueba para múltiples intentos fallidos
void testFailedLoginAttemptsPattern() {
    using namespace mc_security;

    AuditManager::logEvent("Failed Login - User: test_user", AuditManager::EventLevel::WARNING);
    AuditManager::logEvent("Failed Login - User: test_user", AuditManager::EventLevel::WARNING);
    AuditManager::logEvent("Failed Login - User: test_user", AuditManager::EventLevel::WARNING);
    AuditManager::logEvent("Failed Login - User: test_user", AuditManager::EventLevel::WARNING);

    // Analizar patrones para detectar múltiples intentos fallidos
    AuditManager::analyzePatterns();
    std::cout << "Prueba de detección de múltiples intentos fallidos: COMPLETADA (verificar alerta en consola)." << std::endl;
}

// Prueba para integración con log_distributor
void testLogDistributorIntegration() {
    using namespace mc_security;

    const std::string logFilePath = "log_distributor_test.txt";
    AuditManager::setLogFile(logFilePath);

    // Registrar un evento y enviarlo al sistema central
    AuditManager::logEvent("Prueba de integración con log_distributor.", AuditManager::EventLevel::INFO);

    // Simular recuperación desde log_distributor
    auto retrievedLogs = RetrieveLogsFromCentral("Node1");

    // Validar que los logs se enviaron y recuperaron correctamente
    assert(!retrievedLogs.empty() && "Error: No se recuperaron logs del sistema central.");
    assert(retrievedLogs[0].find("Prueba de integración con log_distributor.") != std::string::npos &&
           "Error: El log recuperado no coincide con el enviado.");

    std::cout << "Prueba de integración con log_distributor: PASADA." << std::endl;
}

// Prueba de patrones en logs distribuidos
void testDistributedPatternAnalysis() {
    using namespace mc_security;

    std::vector<std::string> nodes = {"Node1", "Node2", "Node3"};

    // Simular envío de eventos críticos a nodos distribuidos
    SendLogToCentral("Node1", "Failed Login - User: user1");
    SendLogToCentral("Node2", "Failed Login - User: user1");
    SendLogToCentral("Node3", "Failed Login - User: user1");

    // Ejecutar análisis de patrones distribuidos
    AuditManager::analyzeDistributedPatterns(nodes);

    std::cout << "Prueba de análisis de patrones en logs distribuidos: COMPLETADA (verificar alertas en consola)." << std::endl;
}

int main() {
    std::cout << "Iniciando pruebas para 'AuditManager'." << std::endl;

    // Ejecución de pruebas existentes
    testLogEvent();
    testAnalyzePatterns();
    testConcurrentLogging();
    testEncryptedLogs();
    testFailedLoginAttemptsPattern();

    // Nuevas pruebas para log_distributor
    testLogDistributorIntegration();
    testDistributedPatternAnalysis();

    std::cout << "Todas las pruebas para 'AuditManager' completadas exitosamente." << std::endl;
    return 0;
}
