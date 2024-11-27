#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace mc_version {

    // Versión principal, secundaria y de parche
    constexpr int VERSION_MAJOR = 1;
    constexpr int VERSION_MINOR = 0;
    constexpr int VERSION_PATCH = 0;

    // Fecha de lanzamiento de esta versión
    constexpr const char* RELEASE_DATE = "2024-11-14";

    // Descripción breve de la versión
    constexpr const char* VERSION_DESCRIPTION = "Versión inicial de lanzamiento con funcionalidades completas para MC++ 1.0";

    // Función para obtener la versión en formato legible
    inline std::string getVersion() {
        return "MC++ " + std::to_string(VERSION_MAJOR) + "." + 
               std::to_string(VERSION_MINOR) + "." + 
               std::to_string(VERSION_PATCH);
    }

    // Función para obtener la fecha de lanzamiento
    inline std::string getReleaseDate() {
        return RELEASE_DATE;
    }

    // Función para obtener la descripción de la versión
    inline std::string getVersionDescription() {
        return VERSION_DESCRIPTION;
    }

} // namespace mc_version

#endif // VERSION_H
