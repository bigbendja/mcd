#include "file_utils.h"
#include <filesystem>
#include <iostream>

namespace mc_utils {

    std::string FileUtils::readFile(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if (!file) {
            throw std::runtime_error("Error al abrir el archivo para lectura: " + filePath);
        }

        std::ostringstream contentStream;
        contentStream << file.rdbuf();
        file.close();
        return contentStream.str();
    }

    void FileUtils::writeFile(const std::string& filePath, const std::string& content) {
        std::ofstream file(filePath, std::ios::out | std::ios::trunc | std::ios::binary);
        if (!file) {
            throw std::runtime_error("Error al abrir el archivo para escritura: " + filePath);
        }

        file << content;
        file.close();
    }

    std::vector<std::string> FileUtils::readLines(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file) {
            throw std::runtime_error("Error al abrir el archivo para lectura de líneas: " + filePath);
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
        return lines;
    }

    void FileUtils::writeLines(const std::string& filePath, const std::vector<std::string>& lines) {
        std::ofstream file(filePath, std::ios::out | std::ios::trunc);
        if (!file) {
            throw std::runtime_error("Error al abrir el archivo para escritura de líneas: " + filePath);
        }

        for (const auto& line : lines) {
            file << line << '\n';
        }
        file.close();
    }

    bool FileUtils::fileExists(const std::string& filePath) {
        return std::filesystem::exists(filePath);
    }

    void FileUtils::deleteFile(const std::string& filePath) {
        if (!std::filesystem::remove(filePath)) {
            throw std::runtime_error("Error al eliminar el archivo: " + filePath);
        }
    }

    std::streamsize FileUtils::getFileSize(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file) {
            throw std::runtime_error("Error al abrir el archivo para obtener el tamaño: " + filePath);
        }

        std::streamsize size = file.tellg();
        file.close();
        return size;
    }

} // namespace mc_utils
