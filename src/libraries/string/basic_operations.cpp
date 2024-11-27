#include "basic_operations.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

std::string BasicOperations::concatenate(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}

std::string BasicOperations::substring(const std::string& text, int start, int length) {
    if (start < 0 || length < 0 || start >= static_cast<int>(text.length()) || start + length > static_cast<int>(text.length())) {
        throw std::out_of_range("Error: Índices fuera de rango en substring.");
    }
    return text.substr(start, length);
}

int BasicOperations::indexOf(const std::string& text, const std::string& target, int start) {
    if (start < 0 || start >= static_cast<int>(text.length())) {
        throw std::out_of_range("Error: Índice de inicio fuera de rango en indexOf.");
    }
    auto pos = text.find(target, start);
    return (pos != std::string::npos) ? static_cast<int>(pos) : -1;
}

std::string BasicOperations::replace(const std::string& text, const std::string& oldSub, const std::string& newSub, int count) {
    std::string result = text;
    size_t pos = 0;
    int occurrences = 0;
    while ((pos = result.find(oldSub, pos)) != std::string::npos && (count == -1 || occurrences < count)) {
        result.replace(pos, oldSub.length(), newSub);
        pos += newSub.length();
        ++occurrences;
    }
    return result;
}

std::vector<std::string> BasicOperations::split(const std::string& text, const std::string& delimiter, int maxSplits) {
    if (delimiter.empty()) throw std::invalid_argument("Error: El delimitador no puede estar vacío.");
    std::vector<std::string> result;
    size_t start = 0, end;
    int splits = 0;
    while ((end = text.find(delimiter, start)) != std::string::npos && (maxSplits == -1 || splits < maxSplits)) {
        result.push_back(text.substr(start, end - start));
        start = end + delimiter.length();
        ++splits;
    }
    result.push_back(text.substr(start));
    return result;
}

std::string BasicOperations::join(const std::vector<std::string>& elements, const std::string& delimiter) {
    if (elements.empty()) return "";
    std::ostringstream oss;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) oss << delimiter;
        oss << elements[i];
    }
    return oss.str();
}

std::string BasicOperations::reverse(const std::string& text) {
    return std::string(text.rbegin(), text.rend());
}

int BasicOperations::countChar(const std::string& text, char charToCount) {
    return std::count(text.begin(), text.end(), charToCount);
}
