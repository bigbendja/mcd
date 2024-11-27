#include "file_management.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <map>
#include <future>

using FILE_HANDLE = std::shared_ptr<std::fstream>;

// Función auxiliar para verificar el estado del archivo
void validateFile(FILE_HANDLE file, std::ios_base::openmode mode, const std::string& operation) {
    if (!file || !file->is_open()) {
        throw std::runtime_error("Error: Archivo no está abierto para " + operation);
    }

    if ((mode & std::ios::in) && !(file->rdstate() & std::ios::in)) {
        throw std::runtime_error("Error: Archivo no está en modo lectura para " + operation);
    }

    if ((mode & std::ios::out) && !(file->rdstate() & std::ios::out)) {
        throw std::runtime_error("Error: Archivo no está en modo escritura para " + operation);
    }
}

FILE_HANDLE OPEN_FILE(const std::string& path, const std::string& mode) {
    std::ios_base::openmode open_mode;
    if (mode == "r") open_mode = std::ios::in;
    else if (mode == "w") open_mode = std::ios::out;
    else if (mode == "a") open_mode = std::ios::app;
    else throw std::invalid_argument("Error: Modo de archivo no válido");

    FILE_HANDLE file = std::make_shared<std::fstream>(path, open_mode);
    if (!file->is_open()) throw std::runtime_error("Error: No se pudo abrir el archivo en el modo especificado");
    return file;
}

bool CLOSE_FILE(FILE_HANDLE file) {
    if (file && file->is_open()) {
        file->close();
        return true;
    }
    return false;
}

std::string READ_FILE(FILE_HANDLE file, int num_bytes = -1) {
    validateFile(file, std::ios::in, "lectura");

    std::string content;
    if (num_bytes == -1) {
        file->seekg(0, std::ios::end);
        content.resize(file->tellg());
        file->seekg(0, std::ios::beg);
        file->read(&content[0], content.size());
    } else {
        content.resize(num_bytes);
        file->read(&content[0], num_bytes);
    }
    return content;
}

std::future<std::string> READ_FILE_ASYNC(FILE_HANDLE file, int num_bytes = -1) {
    return std::async(std::launch::async, [=] {
        return READ_FILE(file, num_bytes);
    });
}

bool WRITE_FILE(FILE_HANDLE file, const std::string& data) {
    validateFile(file, std::ios::out, "escritura");
    (*file) << data;
    return file->good();
}

std::future<bool> WRITE_FILE_ASYNC(FILE_HANDLE file, const std::string& data) {
    return std::async(std::launch::async, [=] {
        return WRITE_FILE(file, data);
    });
}

std::vector<std::string> READ_LINES(FILE_HANDLE file) {
    validateFile(file, std::ios::in, "lectura");

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(*file, line)) lines.push_back(line);
    return lines;
}

bool WRITE_LINES(FILE_HANDLE file, const std::vector<std::string>& lines) {
    validateFile(file, std::ios::out, "escritura");

    for (const auto& line : lines) (*file) << line << "\n";
    return file->good();
}

bool APPEND_FILE(const std::string& path, const std::string& data) {
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) throw std::runtime_error("Error: No se pudo abrir el archivo para agregar datos");
    file << data;
    return file.good();
}

bool DELETE_FILE(const std::string& path) {
    return std::filesystem::remove(path);
}

bool FILE_EXISTS(const std::string& path) {
    return std::filesystem::exists(path);
}

bool COPY_FILE(const std::string& source_path, const std::string& destination_path) {
    try {
        std::filesystem::copy(source_path, destination_path, std::filesystem::copy_options::overwrite_existing);
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

bool MOVE_FILE(const std::string& source_path, const std::string& destination_path) {
    if (COPY_FILE(source_path, destination_path)) return DELETE_FILE(source_path);
    return false;
}

int GET_FILE_SIZE(FILE_HANDLE file) {
    validateFile(file, std::ios::in, "lectura");
    file->seekg(0, std::ios::end);
    int size = file->tellg();
    file->seekg(0, std::ios::beg);
    return size;
}

std::map<std::string, std::string> GET_FILE_INFO(const std::string& path) {
    if (!FILE_EXISTS(path)) throw std::runtime_error("Error: Archivo no encontrado");

    std::map<std::string, std::string> info;
    info["size"] = std::to_string(std::filesystem::file_size(path));
    info["permissions"] = std::to_string(static_cast<int>(std::filesystem::status(path).permissions()));
    auto last_write_time = std::filesystem::last_write_time(path);
    info["last_write_time"] = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(last_write_time.time_since_epoch()).count());

    return info;
}
