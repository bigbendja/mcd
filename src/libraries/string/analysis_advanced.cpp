#include "analysis_advanced.h"
#include <cctype>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>

int AnalysisAdvanced::length(const std::string& text) {
    return static_cast<int>(text.size());
}

int AnalysisAdvanced::countOccurrences(const std::string& text, const std::string& target) {
    if (target.empty()) {
        throw std::invalid_argument("El parámetro 'target' no puede estar vacío.");
    }

    int count = 0;
    for (size_t pos = text.find(target); pos != std::string::npos; pos = text.find(target, pos + target.size())) {
        count++;
    }
    return count;
}

bool AnalysisAdvanced::isEmpty(const std::string& text) {
    return text.empty();
}

bool AnalysisAdvanced::startsWith(const std::string& text, const std::string& prefix) {
    return text.compare(0, prefix.size(), prefix) == 0;
}

bool AnalysisAdvanced::endsWith(const std::string& text, const std::string& suffix) {
    if (suffix.empty()) return true;
    if (text.size() < suffix.size()) return false;
    return text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool AnalysisAdvanced::containsOnlyAlpha(const std::string& text) {
    return std::all_of(text.begin(), text.end(), ::isalpha);
}

bool AnalysisAdvanced::containsOnlyDigits(const std::string& text) {
    return std::all_of(text.begin(), text.end(), ::isdigit);
}

int AnalysisAdvanced::wordCount(const std::string& text) {
    std::istringstream stream(text);
    return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

std::map<char, int> AnalysisAdvanced::charFrequency(const std::string& text) {
    std::map<char, int> frequency;
    for (char c : text) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            frequency[c]++;
        }
    }
    return frequency;
}

char AnalysisAdvanced::findFirstNonRepeatedChar(const std::string& text) {
    auto frequency = charFrequency(text);
    for (char c : text) {
        if (frequency[c] == 1) {
            return c;
        }
    }
    return '\0';  // Retorna '\0' si no hay caracteres únicos
}

float AnalysisAdvanced::jaccardSimilarity(const std::string& str1, const std::string& str2) {
    if (str1.empty() && str2.empty()) return 1.0f;

    std::set<std::string> set1, set2;
    std::istringstream stream1(str1), stream2(str2);
    std::string word;

    for (; stream1 >> word; set1.insert(word));
    for (; stream2 >> word; set2.insert(word));

    std::vector<std::string> intersection, unionSet;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(intersection));
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(unionSet));

    return unionSet.empty() ? 0.0f : static_cast<float>(intersection.size()) / unionSet.size();
}
