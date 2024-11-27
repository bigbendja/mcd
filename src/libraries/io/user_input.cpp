#include "user_input.h"
#include <iostream>
#include <stdexcept>
#include <regex>

// Función auxiliar para validación de patrones con regex
bool validateWithRegex(const std::string& input, const std::string& pattern, const std::string& error_message) {
    std::regex regex_pattern(pattern);
    if (!std::regex_match(input, regex_pattern)) {
        throw std::runtime_error(error_message);
    }
    return true;
}

// Funciones de entrada y validación
std::string GET_INPUT(const std::string& prompt, bool required, int max_length) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);

    if (required && input.empty()) {
        throw std::runtime_error("Error: Entrada requerida no proporcionada");
    }
    if (max_length != -1 && static_cast<int>(input.size()) > max_length) {
        throw std::runtime_error("Error: Entrada excede la longitud máxima permitida");
    }
    return input;
}

int GET_INT(const std::string& prompt, int min_value, int max_value) {
    std::cout << prompt;
    int value;
    std::cin >> value;

    if (value < min_value || value > max_value) {
        throw std::runtime_error("Error: Entrada fuera del rango de enteros permitidos");
    }
    return value;
}

float GET_FLOAT(const std::string& prompt, float min_value, float max_value) {
    std::cout << prompt;
    float value;
    std::cin >> value;

    if (value < min_value || value > max_value) {
        throw std::runtime_error("Error: Entrada fuera del rango de valores de punto flotante permitidos");
    }
    return value;
}

std::string GET_OPTION(const std::string& prompt, const std::vector<std::string>& options) {
    std::string input;
    std::cout << prompt << " (" << options[0];
    for (size_t i = 1; i < options.size(); ++i) {
        std::cout << "/" << options[i];
    }
    std::cout << "): ";
    std::getline(std::cin, input);

    if (std::find(options.begin(), options.end(), input) == options.end()) {
        throw std::runtime_error("Error: Opción no válida proporcionada");
    }
    return input;
}

bool GET_CONFIRMATION(const std::string& prompt, bool default_yes) {
    std::string input;
    std::cout << prompt << (default_yes ? " [Y/n]: " : " [y/N]: ");
    std::getline(std::cin, input);

    return (input.empty() && default_yes) || input == "y" || input == "Y";
}

std::string GET_PASSWORD(const std::string& prompt, int min_length, int max_length, bool require_special) {
    std::string password;
    std::cout << prompt << " (Oculto): ";
    std::getline(std::cin, password);

    if (password.size() < static_cast<size_t>(min_length) || password.size() > static_cast<size_t>(max_length)) {
        throw std::runtime_error("Error: Contraseña fuera de los límites de longitud permitidos");
    }
    if (require_special && password.find_first_of("!@#$%^&*()_+") == std::string::npos) {
        throw std::runtime_error("Error: La contraseña debe contener al menos un carácter especial");
    }
    return password;
}

std::string GET_EMAIL(const std::string& prompt) {
    std::string email = GET_INPUT(prompt, true);
    validateWithRegex(email, R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)", "Error: Formato de correo electrónico no válido");
    return email;
}

std::string GET_DATE(const std::string& prompt, const std::string& format) {
    std::string date = GET_INPUT(prompt + " (" + format + "): ", true);
    validateWithRegex(date, R"(\d{4}-\d{2}-\d{2})", "Error: Formato de fecha no válido");
    return date;
}

std::string GET_PHONE_NUMBER(const std::string& prompt, const std::string& country_code) {
    std::string phone = GET_INPUT(prompt + " (Código de país " + country_code + "): ", true);
    validateWithRegex(phone, R"(\+?\d+(-\d+)*)", "Error: Número de teléfono no válido");
    return phone;
}
