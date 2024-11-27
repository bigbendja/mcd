#include "io.h"
#include "file_reader.h"
#include "file_writer.h"
#include <cassert>
#include <iostream>
#include <vector>

// Función auxiliar para ejecutar pruebas unitarias
void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

// Pruebas para la lectura de archivos
void test_file_reading() {
    io::FileReader reader;
    std::string content = reader.readFile("test_input.txt");
    run_test("Lectura de archivo existente", !content.empty());

    std::string non_existent_content = reader.readFile("nonexistent.txt");
    run_test("Lectura de archivo inexistente", non_existent_content.empty());
}

// Pruebas para la escritura de archivos
void test_file_writing() {
    io::FileWriter writer;
    bool write_result = writer.writeFile("output_test.txt", "MC++ test output");
    run_test("Escritura de archivo", write_result);

    std::string verify_content = io::FileReader().readFile("output_test.txt");
    run_test("Verificación de contenido escrito", verify_content == "MC++ test output");
}

// Pruebas para la función de apéndice en archivos
void test_file_append() {
    io::FileWriter writer;
    bool append_result = writer.appendToFile("append_test.txt", "First Line\n");
    run_test("Apéndice inicial en archivo", append_result);

    append_result = writer.appendToFile("append_test.txt", "Second Line\n");
    run_test("Apéndice adicional en archivo", append_result);

    std::string content = io::FileReader().readFile("append_test.txt");
    run_test("Verificación de contenido con apéndices", content == "First Line\nSecond Line\n");
}

// Pruebas para el manejo de archivos binarios
void test_binary_file_handling() {
    std::vector<uint8_t> data = {0x42, 0x4D, 0xCC, 0xDD}; // Datos de prueba binarios
    bool binary_write_result = io::FileWriter().writeBinaryFile("binary_test.bin", data);
    run_test("Escritura de archivo binario", binary_write_result);

    std::vector<uint8_t> binary_content = io::FileReader().readBinaryFile("binary_test.bin");
    run_test("Lectura de archivo binario", binary_content == data);
}

// Pruebas para la funcionalidad de existencia de archivo
void test_file_existence() {
    bool exists = io::FileReader().fileExists("output_test.txt");
    run_test("Verificación de archivo existente", exists);

    bool not_exists = io::FileReader().fileExists("nonexistent.txt");
    run_test("Verificación de archivo inexistente", !not_exists);
}

// Pruebas de configuración
void test_io_configuration() {
    config::load_config("./config/io_config.json");

    std::string default_directory = config::get_setting<std::string>("io.default_directory");
    run_test("Ruta de directorio por defecto cargada", !default_directory.empty());

    int read_buffer_size = config::get_setting<int>("io.read_buffer_size");
    run_test("Buffer de lectura configurado", read_buffer_size > 0);
}

int main() {
    std::cout << "Iniciando pruebas para la librería 'io'" << std::endl;

    test_file_reading();
    test_file_writing();
    test_file_append();
    test_binary_file_handling();
    test_file_existence();
    test_io_configuration();

    std::cout << "Pruebas completadas." << std::endl;
    return 0;
}
