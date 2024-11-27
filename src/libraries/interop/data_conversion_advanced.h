#ifndef DATA_CONVERSION_ADVANCED_H
#define DATA_CONVERSION_ADVANCED_H

#include <string>
#include <map>
#include <list>

class DataConversionAdvanced {
public:
    // Conversión de mapa a JSON
    static std::string toJson(const std::map<std::string, std::string>& data);
    
    // Conversión de JSON a mapa
    static std::map<std::string, std::string> fromJson(const std::string& jsonData);

    // Conversión de número a cadena con precisión
    static std::string numberToString(double number, int precision = 6);

    // Conversión de cadena a número
    static double stringToNumber(const std::string& numberString);

    // Conversión de fecha a cadena
    static std::string dateToString(const std::string& date, const std::string& format = defaultDateFormat);

    // Conversión de cadena a fecha
    static std::string stringToDate(const std::string& dateString, const std::string& format = defaultDateFormat);

    // Conversión de codificación de texto
    static std::string convertEncoding(const std::string& text, const std::string& fromEncoding = defaultEncoding, const std::string& toEncoding = defaultEncoding);

    // Conversión de datos binarios a hexadecimal
    static std::string binaryToHex(const std::string& binaryData);

    // Conversión de cadena hexadecimal a binario
    static std::string hexToBinary(const std::string& hexString);

    // Conversión de datos binarios a Base64
    static std::string binaryToBase64(const std::string& binaryData);

    // Conversión de Base64 a datos binarios
    static std::string base64ToBinary(const std::string& base64String);

    // Conversión de lista o mapa a CSV
    static std::string toCsv(const std::list<std::map<std::string, std::string>>& data, char delimiter = ',');

    // Conversión de CSV a lista o mapa
    static std::list<std::map<std::string, std::string>> fromCsv(const std::string& csvData, char delimiter = ',');

    // Conversión de lista a cadena delimitada
    static std::string listToString(const std::list<std::string>& listData, char delimiter = ',');

    // Conversión de cadena delimitada a lista
    static std::list<std::string> stringToList(const std::string& delimitedString, char delimiter = ',');

private:
    // Valores de configuración predeterminados
    static const std::string defaultDateFormat;
    static const std::string defaultEncoding;
};

#endif // DATA_CONVERSION_ADVANCED_H
