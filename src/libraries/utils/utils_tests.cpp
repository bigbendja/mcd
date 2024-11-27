#include "utils.h"
#include "file_utils.h"
#include "string_utils.h"
#include "logger.h"
#include "config.h"
#include <cassert>
#include <iostream>

// Función auxiliar para pruebas unitarias
void run_test(const std::string &test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas para file_utils
void test_file_utils() {
    run_test("Crear archivo de prueba", file_utils::write_to_file("./test_output.txt", "Prueba de escritura"));
    std::string content = file_utils::read_from_file("./test_output.txt");
    run_test("Leer contenido del archivo", content == "Prueba de escritura");
}

// Pruebas para string_utils
void test_string_utils() {
    std::string str = "   Ejemplo de Cadena   ";
    run_test("Recortar espacios en blanco", string_utils::trim(str) == "Ejemplo de Cadena");

    std::string lower_str = string_utils::to_lower("TEXT IN UPPERCASE");
    run_test("Convertir a minúsculas", lower_str == "text in uppercase");

    std::vector<std::string> tokens = string_utils::split("uno,dos,tres", ',');
    run_test("Dividir cadena en tokens", tokens.size() == 3 && tokens[0] == "uno" && tokens[1] == "dos" && tokens[2] == "tres");
}

// Pruebas para logger
void test_logger() {
    logger::set_log_level("INFO");
    run_test("Nivel de log configurado a INFO", logger::get_log_level() == "INFO");

    logger::log_info("Prueba de log de información");
    logger::log_warning("Prueba de log de advertencia");
    logger::log_error("Prueba de log de error");

    // Verificación de tamaño del archivo log para rotación
    std::string log_path = "./logs/utils_log.txt";
    run_test("Verificar rotación de log", file_utils::file_size(log_path) <= 10485760); // Tamaño en bytes
}

// Pruebas para config
void test_config() {
    config::load_config("./config/utils_config.json");

    run_test("Cargar configuración", config::is_loaded());

    std::string log_level = config::get_setting<std::string>("log_settings.log_level");
    run_test("Verificar log_level desde configuración", log_level == "INFO");

    int max_file_size = config::get_setting<int>("file_utils_settings.max_file_size");
    run_test("Verificar max_file_size desde configuración", max_file_size == 5242880);
}

// Pruebas de rendimiento y optimización
void test_performance_settings() {
    bool optimizations_enabled = config::get_setting<bool>("performance_settings.enable_optimizations");
    run_test("Verificar optimizaciones habilitadas", optimizations_enabled);

    int cache_size_limit = config::get_setting<int>("performance_settings.cache_size_limit_mb");
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
