#include "data_conversion_advanced.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <json/json.h> // Para manejo JSON
#include <vector>
#include <regex>
#include <algorithm>
#include <bitset>

// Valores predeterminados para formatos
const std::string DataConversionAdvanced::defaultDateFormat = "YYYY-MM-DD";
const std::string DataConversionAdvanced::defaultEncoding = "UTF-8";

// Función para convertir un mapa a JSON
std::string DataConversionAdvanced::toJson(const std::map<std::string, std::string>& data) {
    Json::Value jsonData;
    for (const auto& pair : data) {
        jsonData[pair.first] = pair.second;
    }
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, jsonData);
}

// Función para convertir JSON a un mapa
std::map<std::string, std::string> DataConversionAdvanced::fromJson(const std::string& jsonData) {
    Json::CharReaderBuilder reader;
    Json::Value jsonValue;
    std::istringstream jsonStream(jsonData);
    std::string errors;
    std::map<std::string, std::string> result;

    if (!Json::parseFromStream(reader, jsonStream, &jsonValue, &errors)) {
        throw std::runtime_error("Error al convertir JSON a mapa: " + errors);
    }
    for (const auto& key : jsonValue.getMemberNames()) {
        result[key] = jsonValue[key].asString();
    }
    return result;
}

// Conversión de números a cadenas con precisión específica
std::string DataConversionAdvanced::numberToString(double number, int precision) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << number;
    return out.str();
}

// Conversión de cadenas a números
double DataConversionAdvanced::stringToNumber(const std::string& numberString) {
    try {
        return std::stod(numberString);
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error: No se pudo convertir la cadena a número.");
    }
}

// Validación de formato de fecha antes de conversión
std::string DataConversionAdvanced::dateToString(const std::string& date, const std::string& format) {
    std::regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    if (!std::regex_match(date, datePattern)) {
        throw std::invalid_argument("Error: Fecha no cumple con el formato esperado (YYYY-MM-DD).");
    }
    return date; // Asume que está en el formato esperado
}

// Conversión de cadena a fecha con validación de formato
std::string DataConversionAdvanced::stringToDate(const std::string& dateString, const std::string& format) {
    return dateToString(dateString, format);
}

// Conversión de texto entre codificaciones
std::string DataConversionAdvanced::convertEncoding(const std::string& text, const std::string& fromEncoding, const std::string& toEncoding) {
    // Implementar según bibliotecas modernas o externas, si es necesario
    return text; // Para demostración
}

// Conversión de datos binarios a cadena hexadecimal
std::string DataConversionAdvanced::binaryToHex(const std::string& binaryData) {
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (unsigned char byte : binaryData) {
        hexStream << std::setw(2) << static_cast<int>(byte);
    }
    return hexStream.str();
}

// Conversión de cadena hexadecimal a datos binarios
std::string DataConversionAdvanced::hexToBinary(const std::string& hexString) {
    if (hexString.size() % 2 != 0) {
        throw std::invalid_argument("Error: Cadena hexadecimal con longitud impar.");
    }

    std::string binaryData;
    for (size_t i = 0; i < hexString.size(); i += 2) {
        std::string byteString = hexString.substr(i, 2);
        binaryData.push_back(static_cast<char>(std::stoi(byteString, nullptr, 16)));
    }
    return binaryData;
}

// Conversión de datos binarios a Base64
std::string DataConversionAdvanced::binaryToBase64(const std::string& binaryData) {
    // Implementación utilizando bibliotecas modernas si están disponibles
    static const char* base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    std::string base64;
    int val = 0, valb = -6;
    for (unsigned char c : binaryData) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            base64.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) base64.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (base64.size() % 4) base64.push_back('=');
    return base64;
}

// Conversión de Base64 a datos binarios
std::string DataConversionAdvanced::base64ToBinary(const std::string& base64String) {
    // Implementación de decodificación
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;

    std::string binaryData;
    int val = 0, valb = -8;
    for (unsigned char c : base64String) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            binaryData.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return binaryData;
}
