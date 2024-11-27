#include "uuid.h"
#include <random>
#include <sstream>
#include <iomanip>

namespace mc_utils {

    std::string UUID::generate() {
        // Inicialización del motor aleatorio y distribuciones
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> dis(0, 15);
        static std::uniform_int_distribution<int> dis2(8, 11);

        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        for (int i = 0; i < 8; ++i) ss << dis(gen);               // 8 dígitos para el primer bloque
        ss << "-";
        for (int i = 0; i < 4; ++i) ss << dis(gen);               // 4 dígitos para el segundo bloque
        ss << "-4";                                               // Versión 4 de UUID
        for (int i = 0; i < 3; ++i) ss << dis(gen);               // 3 dígitos adicionales para completar el tercer bloque
        ss << "-";
        ss << dis2(gen);                                          // Primer dígito de variante
        for (int i = 0; i < 3; ++i) ss << dis(gen);               // 3 dígitos para completar el cuarto bloque
        ss << "-";
        for (int i = 0; i < 12; ++i) ss << dis(gen);              // 12 dígitos para el último bloque

        return ss.str();
    }

} // namespace mc_utils
