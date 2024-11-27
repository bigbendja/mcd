#include "utils.h"
#include "file_utils.h"
#include "string_utils.h"
#include "logger.h"
#include "config.h"
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

// Pruebas para file_utils
void test_file_utils() {
    run_test("Escribir archivo de prueba", mc_utils::FileUtils::writeFile("./test_output.txt", "Prueba de escritura"));
    std::string content = mc_utils::FileUtils::readFile("./test_output.txt");
    run_test("Leer contenido del archivo", content == "Prueba de escritura");

    run_test("Añadir a archivo", mc_utils::FileUtils::appendToFile("./test_output.txt", "\nLínea adicional"));
    content = mc_utils::FileUtils::readFile("./test_output.txt");
    run_test("Verificar contenido añadido", content == "Prueba de escritura\nLínea adicional");
}

// Pruebas para string_utils
void test_string_utils() {
    run_test("Convertir a minúsculas", mc_utils::StringUtils::toLower("HELLO") == "hello");
    run_test("Convertir a mayúsculas", mc_utils::StringUtils::toUpper("hello") == "HELLO");

    auto tokens = mc_utils::StringUtils::split("uno,dos,tres", ',');
    run_test("Dividir cadena en tokens", tokens.size() == 3 && tokens[0] == "uno" && tokens[1] == "dos" && tokens[2] == "tres");

    std::vector<std::string> words = {"uno", "dos", "tres"};
    run_test("Unir tokens en cadena", mc_utils::StringUtils::join(words, ',') == "uno,dos,tres");
}

// Pruebas para logger
void test_logger() {
    mc_utils::Logger::setLogLevel("INFO");
    run_test("Nivel de log configurado a INFO", mc_utils::Logger::getLogLevel() == "INFO");

    mc_utils::Logger::logInfo("Mensaje de información de prueba");
    mc_utils::Logger::logWarning("Mensaje de advertencia de prueba");
    mc_utils::Logger::logError("Mensaje de error de prueba");

    std::string log_path = "./logs/utils_log.txt";
    run_test("Verificar rotación de log", mc_utils::FileUtils::fileSize(log_path) <= 10485760); // Tamaño en bytes
}

// Pruebas para config
void test_config() {
    mc_utils::Config::loadConfig("./config/utils_config.json");
    run_test("Cargar configuración", mc_utils::Config::isLoaded());

    std::string log_level = mc_utils::Config::getSetting<std::string>("log_settings.log_level");
    run_test("Verificar log_level desde configuración", log_level == "INFO");

    int max_file_size = mc_utils::Config::getSetting<int>("file_utils.max_file_size");
    run_test("Verificar max_file_size desde configuración", max_file_size == 5242880);
}

// Pruebas de rendimiento y optimización
void test_performance_settings() {
    bool optimizations_enabled = mc_utils::Config::getSetting<bool>("performance_settings.enable_optimizations");
    run_test("Verificar optimizaciones habilitadas", optimizations_enabled);

    int cache_size_limit = mc_utils::Config::getSetting<int>("performance_settings.cache_size_limit_mb");
    run_test("Verificar límite de tamaño de caché", cache_size_limit == 50);
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'utils'" << std::endl;

    test_file_utils();
    test_string_utils();
    test_logger();
    test_config();
    test_performance_settings();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
