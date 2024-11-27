#include "text_transformation.h"
#include <cctype>
#include <algorithm>

/**
 * @brief Convierte todos los caracteres de una cadena a mayúsculas.
 * @param text Cadena de entrada.
 * @return Cadena en mayúsculas.
 */
std::string TextTransformation::toUpper(const std::string& text) {
    std::string result(text.size(), '\0');
    std::transform(text.begin(), text.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
    return result;
}

/**
 * @brief Convierte todos los caracteres de una cadena a minúsculas.
 * @param text Cadena de entrada.
 * @return Cadena en minúsculas.
 */
std::string TextTransformation::toLower(const std::string& text) {
    std::string result(text.size(), '\0');
    std::transform(text.begin(), text.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

/**
 * @brief Capitaliza el primer carácter de una cadena, poniendo en minúsculas el resto.
 * @param text Cadena de entrada.
 * @return Cadena con el primer carácter en mayúsculas y el resto en minúsculas.
 */
std::string TextTransformation::capitalize(const std::string& text) {
    if (text.empty()) return text;
    std::string result = toLower(text);
    result[0] = std::toupper(static_cast<unsigned char>(result[0]));
    return result;
}

/**
 * @brief Elimina los espacios en blanco al inicio y al final de la cadena.
 * @param text Cadena de entrada.
 * @return Cadena sin espacios en los extremos.
 */
std::string TextTransformation::trim(const std::string& text) {
    size_t start = text.find_first_not_of(" \t\n\r\f\v");
    size_t end = text.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : text.substr(start, end - start + 1);
}

/**
 * @brief Elimina todos los espacios en blanco de una cadena.
 * @param text Cadena de entrada.
 * @return Cadena sin espacios.
 */
std::string TextTransformation::removeWhitespace(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    std::copy_if(text.begin(), text.end(), std::back_inserter(result), [](unsigned char c) { return !std::isspace(c); });
    return result;
}

/**
 * @brief Reemplaza todas las ocurrencias de un carácter en una cadena por otro carácter.
 * @param text Cadena de entrada.
 * @param target Carácter a reemplazar.
 * @param replacement Carácter de reemplazo.
 * @return Cadena con los caracteres reemplazados.
 */
std::string TextTransformation::replaceChar(const std::string& text, char target, char replacement) {
    std::string result = text;
    std::replace(result.begin(), result.end(), target, replacement);
    return result;
}

/**
 * @brief Convierte una cadena a "Title Case" (cada palabra empieza con mayúscula).
 * @param text Cadena de entrada.
 * @return Cadena en formato Title Case.
 */
std::string TextTransformation::toTitleCase(const std::string& text) {
    std::string result = toLower(text);
    bool capitalizeNext = true;
    for (char& c : result) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            c = std::toupper(static_cast<unsigned char>(c));
            capitalizeNext = false;
        }
    }
    return result;
}

/**
 * @brief Convierte una cadena a formato "snake_case" (palabras separadas por guión bajo).
 * @param text Cadena de entrada.
 * @return Cadena en formato snake_case.
 */
std::string TextTransformation::toSnakeCase(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    for (char c : text) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            result += '_';
        } else if (std::isupper(static_cast<unsigned char>(c))) {
            if (!result.empty()) result += '_';
            result += std::tolower(static_cast<unsigned char>(c));
        } else {
            result += c;
        }
    }
    return trim(result);
}

/**
 * @brief Convierte una cadena a formato "kebab-case" (palabras separadas por guión medio).
 * @param text Cadena de entrada.
 * @return Cadena en formato kebab-case.
 */
std::string TextTransformation::toKebabCase(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    for (char c : text) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            result += '-';
        } else if (std::isupper(static_cast<unsigned char>(c))) {
            if (!result.empty()) result += '-';
            result += std::tolower(static_cast<unsigned char>(c));
        } else {
            result += c;
        }
    }
    return trim(result);
}
