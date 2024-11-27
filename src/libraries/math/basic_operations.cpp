#include "basic_operations.h"
#include <stdexcept>
#include <cmath>
#include <limits>

// Suma con validación de desbordamiento
template <typename T>
T BasicOperations::add(T a, T b) {
    if constexpr (std::is_integral_v<T>) {
        if (a > std::numeric_limits<T>::max() - b) {
            throw std::overflow_error("Overflow Error: Resultado de suma excede el rango máximo permitido.");
        }
    }
    return a + b;
}

// Resta con validación de subdesbordamiento
template <typename T>
T BasicOperations::subtract(T a, T b) {
    if constexpr (std::is_integral_v<T>) {
        if (a < std::numeric_limits<T>::min() + b) {
            throw std::underflow_error("Underflow Error: Resultado de resta excede el rango mínimo permitido.");
        }
    }
    return a - b;
}

// Multiplicación con validación de desbordamiento
template <typename T>
T BasicOperations::multiply(T a, T b) {
    if constexpr (std::is_integral_v<T>) {
        if (a != 0 && b != 0 && std::abs(a) > std::numeric_limits<T>::max() / std::abs(b)) {
            throw std::overflow_error("Overflow Error: Resultado de multiplicación excede el rango máximo permitido.");
        }
    }
    return a * b;
}

// División con manejo de errores
template <typename T>
T BasicOperations::divide(T a, T b) {
    if (b == 0) {
        throw std::invalid_argument("Invalid Argument Error: División por cero no permitida.");
    }
    if constexpr (std::is_floating_point_v<T>) {
        if (std::abs(b) < std::numeric_limits<T>::epsilon()) {
            throw std::domain_error("Domain Error: Divisor demasiado pequeño para tipos de punto flotante.");
        }
    }
    return static_cast<T>(a) / b;
}
