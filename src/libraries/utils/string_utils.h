#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <locale>

namespace mc_utils {

    class StringUtils {
    public:
        // Convierte una cadena a minúsculas
        static std::string toLower(const std::string& str);

        // Convierte una cadena a mayúsculas
        static std::string toUpper(const std::string& str);

        // Divide una cadena en partes usando un delimitador
        static std::vector<std::string> split(const std::string& str, char delimiter);

        // Une un vector de cadenas en una sola cadena, con un delimitador
        static std::string join(const std::vector<std::string>& elements, char delimiter);

        // Elimina espacios en blanco del inicio y final de la cadena
        static std::string trim(const std::string& str);

        // Reemplaza todas las ocurrencias de una subcadena por otra
        static std::string replaceAll(const std::string& str, const std::string& from, const std::string& to);

        // Comprueba si una cadena comienza con un prefijo determinado
        static bool startsWith(const std::string& str, const std::string& prefix);

        // Comprueba si una cadena termina con un sufijo determinado
        static bool endsWith(const std::string& str, const std::string& suffix);

        // Convierte cualquier valor numérico a una cadena con precisión específica
        template <typename T>
        static std::string toStringWithPrecision(const T value, const int precision);
    };

} // namespace mc_utils

#include "string_utils.hpp"

#endif // STRING_UTILS_H
