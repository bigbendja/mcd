#include "output_formatting.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <codecvt>

// -------------------------------------
// Impresión básica
// -------------------------------------

void PRINT(const std::string& text, const std::string& end) {
    std::cout << text << end;
}

void PRINT_FORMATTED(const std::string& template_text, const std::map<std::string, std::string>& values) {
    std::string formatted_text = template_text;
    for (const auto& pair : values) {
        std::string placeholder = "{" + pair.first + "}";
        size_t pos = formatted_text.find(placeholder);
        while (pos != std::string::npos) {
            formatted_text.replace(pos, placeholder.length(), pair.second);
            pos = formatted_text.find(placeholder, pos + pair.second.length());
        }
    }
    std::cout << formatted_text << "\n";
}

// -------------------------------------
// Tablas y Formatos JSON
// -------------------------------------

void PRINT_TABLE(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& headers, int padding) {
    std::vector<size_t> widths;
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (i >= widths.size()) widths.push_back(0);
            widths[i] = std::max(widths[i], row[i].length() + padding);
        }
    }

    if (!headers.empty()) {
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << std::setw(widths[i]) << headers[i] << " ";
        }
        std::cout << "\n";
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << std::setw(widths[i]) << row[i] << " ";
        }
        std::cout << "\n";
    }
}

void PRINT_JSON(const std::map<std::string, std::string>& data, int indent) {
    std::string indentation(indent, ' ');
    std::cout << "{\n";
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << indentation << "\"" << it->first << "\": \"" << it->second << "\"";
        if (std::next(it) != data.end()) std::cout << ",";
        std::cout << "\n";
    }
    std::cout << "}\n";
}

// -------------------------------------
// Mensajes de Estado
// -------------------------------------

void PRINT_ERROR(const std::string& message) {
    std::cout << "\033[1;31mERROR: " << message << "\033[0m\n";
}

void PRINT_WARNING(const std::string& message) {
    std::cout << "\033[1;33mWARNING: " << message << "\033[0m\n";
}

void PRINT_SUCCESS(const std::string& message) {
    std::cout << "\033[1;32mSUCCESS: " << message << "\033[0m\n";
}

void PRINT_LOG(const std::string& message, const std::string& level) {
    std::string color;
    if (level == "ERROR") color = "\033[1;31m";
    else if (level == "WARNING") color = "\033[1;33m";
    else color = "\033[1;34m";  // INFO
    std::cout << color << "[" << level << "] " << message << "\033[0m\n";
}

// -------------------------------------
// Formato Avanzado
// -------------------------------------

void PRINT_PROGRESS(int current, int total, int bar_length) {
    if (total <= 0) throw std::invalid_argument("Total must be greater than 0");
    float progress = static_cast<float>(current) / total;
    int filled_length = static_cast<int>(bar_length * progress);
    std::cout << "\r[" << std::string(filled_length, '█') << std::string(bar_length - filled_length, '-') << "] "
              << std::fixed << std::setprecision(2) << (progress * 100) << "%";
    std::cout.flush();
    if (current >= total) std::cout << std::endl;
}

std::string FORMAT_CURRENCY(float amount, const std::string& currency_symbol, int decimal_places) {
    std::ostringstream out;
    out << currency_symbol << std::fixed << std::setprecision(decimal_places) << amount;
    return out.str();
}

std::string FORMAT_DATE(const std::string& date, const std::string& format) {
    struct tm tm = {};
    if (strptime(date.c_str(), "%Y-%m-%d", &tm) == nullptr) throw std::invalid_argument("Date format must be YYYY-MM-DD");
    char buffer[100];
    strftime(buffer, sizeof(buffer), format.c_str(), &tm);
    return std::string(buffer);
}

std::string FORMAT_NUMBER(float number, int decimal_places, bool use_commas) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(decimal_places) << number;
    std::string num_str = out.str();
    if (use_commas) {
        size_t pos = num_str.find('.') - 3;
        while (pos > 0 && pos < num_str.length()) {
            num_str.insert(pos, ",");
            pos -= 3;
        }
    }
    return num_str;
}
