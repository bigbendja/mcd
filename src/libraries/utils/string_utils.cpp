#include "string_utils.h"
#include <cctype>
#include <sstream>
#include <iomanip>

namespace mc_utils {

    std::string StringUtils::toLower(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

    std::string StringUtils::toUpper(const std::string& str) {
        std::string upperStr = str;
        std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
        return upperStr;
    }

    std::vector<std::string> StringUtils::split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item, delimiter)) {
            tokens.push_back(item);
        }
        return tokens;
    }

    std::string StringUtils::join(const std::vector<std::string>& elements, char delimiter) {
        if (elements.empty()) return "";
        std::ostringstream os;
        for (size_t i = 0; i < elements.size() - 1; ++i) {
            os << elements[i] << delimiter;
        }
        os << elements.back();
        return os.str();
    }

    std::string StringUtils::trim(const std::string& str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
            ++start;
        }
        auto end = str.end();
        do {
            --end;
        } while (std::distance(start, end) > 0 && std::isspace(*end));
        return std::string(start, end + 1);
    }

    std::string StringUtils::replaceAll(const std::string& str, const std::string& from, const std::string& to) {
        if (from.empty()) return str;
        std::string result = str;
        size_t startPos = 0;
        while ((startPos = result.find(from, startPos)) != std::string::npos) {
            result.replace(startPos, from.length(), to);
            startPos += to.length();
        }
        return result;
    }

    bool StringUtils::startsWith(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
    }

    bool StringUtils::endsWith(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    template <typename T>
    std::string StringUtils::toStringWithPrecision(const T value, const int precision) {
        std::ostringstream out;
        out << std::fixed << std::setprecision(precision) << value;
        return out.str();
    }

} // namespace mc_utils
