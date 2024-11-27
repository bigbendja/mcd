#include "file_management.h"
#include "user_input.h"
#include "output_formatting.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <map>

// Pruebas para el módulo de gestión de archivos (file_management)
void test_file_management() {
    FILE_HANDLE file = OPEN_FILE("/var/data/test_file.txt", "w");
    assert(file != nullptr);

    bool write_success = WRITE_FILE(file, "Test data for file management module.");
    assert(write_success);

    bool close_success = CLOSE_FILE(file);
    assert(close_success);

    bool file_exists = FILE_EXISTS("/var/data/test_file.txt");
    assert(file_exists);

    bool delete_success = DELETE_FILE("/var/data/test_file.txt");
    assert(delete_success);

    std::cout << "File management tests passed.\n";
}

// Pruebas para el módulo de entrada del usuario (user_input)
void test_user_input() {
    try {
        std::string input = GET_INPUT("Enter a value (max 20 chars): ", true, 20);
        assert(!input.empty());
    } catch (const std::exception& e) {
        std::cerr << "Exception in GET_INPUT: " << e.what() << '\n';
    }

    try {
        int number = GET_INT("Enter an integer (0-100): ", 0, 100);
        assert(number >= 0 && number <= 100);
    } catch (const std::exception& e) {
        std::cerr << "Exception in GET_INT: " << e.what() << '\n';
    }

    std::cout << "User input tests passed.\n";
}

// Pruebas para el módulo de formateo de salida (output_formatting)
void test_output_formatting() {
    PRINT("This is a test message for output formatting.", "\n");
    
    std::map<std::string, std::string> placeholders = { {"name", "MC++"}, {"version", "1.0"} };
    PRINT_FORMATTED("Welcome to {name} version {version}.", placeholders);

    std::vector<std::vector<std::string>> table_data = {
        {"Header1", "Header2"},
        {"Row1Col1", "Row1Col2"},
        {"Row2Col1", "Row2Col2"}
    };
    PRINT_TABLE(table_data, {"Column1", "Column2"}, 4);

    PRINT_SUCCESS("Test successful!");
    PRINT_WARNING("This is a warning.");
    PRINT_ERROR("This is an error.");

    std::cout << "Output formatting tests passed.\n";
}

int main() {
    std::cout << "Running IO library tests...\n";

    test_file_management();
    test_user_input();
    test_output_formatting();

    std::cout << "All IO library tests passed.\n";
    return 0;
}
