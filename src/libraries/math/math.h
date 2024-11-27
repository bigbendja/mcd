#ifndef MATH_H
#define MATH_H

/**
 * @file math.h
 * @brief Header principal de la librería matemática avanzada para MC++.
 *
 * La biblioteca matemática de MC++ está diseñada para proporcionar herramientas eficientes y precisas
 * para cálculos científicos, técnicos y de ingeniería. Este archivo agrupa todas las funcionalidades 
 * de los módulos matemáticos.
 * 
 * @version 1.0
 * @date 2024
 * 
 * ### Módulos incluidos:
 * - **Basic Operations**: Operaciones fundamentales como suma, resta, multiplicación y división.
 * - **Advanced Operations**: Funciones avanzadas como exponenciación, raíces y logaritmos.
 * - **Linear Algebra**: Operaciones básicas de álgebra lineal, incluyendo suma de matrices y determinantes.
 * - **Linear Algebra Advanced**: Multiplicación de matrices, descomposición LU e inversión.
 * - **Combinatorics**: Funciones de cálculo combinatorio como factorial, combinaciones y permutaciones.
 * - **Hyperbolic**: Funciones trigonométricas hiperbólicas avanzadas.
 * - **Trigonometry**: Funciones trigonométricas como seno, coseno y tangente.
 */

// Versión de la biblioteca
#define MC_MATH_VERSION_MAJOR 1
#define MC_MATH_VERSION_MINOR 0
#define MC_MATH_VERSION (MC_MATH_VERSION_MAJOR * 100 + MC_MATH_VERSION_MINOR)

// Inclusión de módulos de operaciones matemáticas
#include "basic_operations.h"
#include "advanced_operations.h"
#include "linear_algebra.h"
#include "linear_algebra_advanced.h"
#include "combinatorics.h"
#include "hyperbolic.h"
#include "trigonometry.h"

#endif // MATH_H
