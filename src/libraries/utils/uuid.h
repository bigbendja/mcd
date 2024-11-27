#ifndef UUID_H
#define UUID_H

#include <string>

namespace mc_utils {

    class UUID {
    public:
        // Genera un UUID en formato estándar, garantizando unicidad y aleatoriedad
        static std::string generate();
    };

} // namespace mc_utils

#endif // UUID_H
