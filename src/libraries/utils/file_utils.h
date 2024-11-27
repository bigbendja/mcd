#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace mc_utils {

    // Clase para manejo de operaciones avanzadas de archivos
    class FileUtils {
    public:
        // Lee el contenido completo de un archivo en una cadena
        static std::string readFile(const std::string& filePath);

        // Escribe una cadena completa en un archivo, sobreescribiendo si existe
        static void writeFile(const std::string& filePath, const std::string& content);

        // Lee líneas de un archivo en un vector de cadenas
        static std::vector<std::string> readLines(const std::string& filePath);

        // Escribe un vector de cadenas en un archivo, línea por línea
        static void writeLines(const std::string& filePath, const std::vector<std::string>& lines);

        // Verifica si un archivo existe en el sistema
        static bool fileExists(const std::string& filePath);

        // Borra un archivo del sistema
        static void deleteFile(const std::string& filePath);

        // Obtiene el tamaño del archivo en bytes
        static std::streamsize getFileSize(const std::string& filePath);
    };

} // namespace mc_utils

#endif // FILE_UTILS_H
