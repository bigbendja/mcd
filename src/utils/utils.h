#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

// Espacio de nombres para funciones y estructuras de utilidad
namespace mc_utils {

    // **1. Estructura avanzada para la generación de identificadores únicos**
    struct UUID {
        static std::string generate() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dis(0, 15);
            static const char* hex_chars = "0123456789ABCDEF";

            std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
            for (char& c : uuid) {
                if (c == 'x') {
                    c = hex_chars[dis(gen)];
                } else if (c == 'y') {
                    c = hex_chars[(dis(gen) & 0x3) | 0x8];
                }
            }
            return uuid;
        }
    };

    // **2. Funciones avanzadas para manipulación de cadenas**
    namespace string_utils {

        std::string to_upper(const std::string& input) {
            std::string result = input;
            for (auto& ch : result) ch = toupper(ch);
            return result;
        }

        std::string to_lower(const std::string& input) {
            std::string result = input;
            for (auto& ch : result) ch = tolower(ch);
            return result;
        }

        std::vector<std::string> split(const std::string& str, char delimiter) {
            std::vector<std::string> tokens;
            std::stringstream ss(str);
            std::string token;
            while (std::getline(ss, token, delimiter)) {
                tokens.push_back(token);
            }
            return tokens;
        }

        std::string join(const std::vector<std::string>& tokens, const std::string& delimiter) {
            std::ostringstream oss;
            for (size_t i = 0; i < tokens.size(); ++i) {
                oss << tokens[i];
                if (i < tokens.size() - 1) oss << delimiter;
            }
            return oss.str();
        }
    }

    // **3. Funciones de fecha y hora para aplicaciones en tiempo real**
    namespace datetime_utils {

        std::string current_timestamp() {
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::ostringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
            return ss.str();
        }

        long long timestamp_ms() {
            auto now = std::chrono::system_clock::now();
            auto duration = now.time_since_epoch();
            return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        }
    }

    // **4. Función de registro de operaciones y auditoría avanzada**
    struct Logger {
        enum Level { INFO, WARNING, ERROR };

        static void log(const std::string& message, Level level = INFO) {
            std::string level_str;
            switch (level) {
                case INFO: level_str = "[INFO]"; break;
                case WARNING: level_str = "[WARNING]"; break;
                case ERROR: level_str = "[ERROR]"; break;
            }
            std::cout << datetime_utils::current_timestamp() << " " << level_str << ": " << message << std::endl;
        }
    };

    // **5. Validación avanzada de datos**
    namespace validation_utils {

        bool is_numeric(const std::string& str) {
            return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
        }

        bool is_alphanumeric(const std::string& str) {
            return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) { return std::isalnum(c); });
        }
    }

    // **6. Módulo de manejo de errores personalizados**
    class MCException : public std::runtime_error {
    public:
        explicit MCException(const std::string& message) : std::runtime_error("MC++ Error: " + message) {}
    };

}

#endif // UTILS_H
