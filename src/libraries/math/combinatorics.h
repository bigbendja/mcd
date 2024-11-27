#ifndef COMBINATORICS_H
#define COMBINATORICS_H

/**
 * Módulo Combinatorics en MC++: Proporciona funciones avanzadas para cálculos combinatorios
 * incluyendo factorial, combinación y permutación.
 */
class Combinatorics {
public:
    /**
     * Calcula el factorial de un número entero no negativo.
     * @param n El número para el cual se calcula el factorial (n!).
     * @return El factorial de n.
     * @throws std::invalid_argument si n es negativo.
     * @throws std::overflow_error si el resultado excede el rango permitido de enteros.
     */
    static int factorial(int n);

    /**
     * Calcula el número de combinaciones posibles (nCr).
     * @param n Número total de elementos.
     * @param r Número de elementos seleccionados.
     * @return Número de combinaciones posibles.
     * @throws std::invalid_argument si n o r son negativos, o si r es mayor que n.
     * @throws std::overflow_error si el resultado excede el rango permitido de enteros.
     */
    static int combination(int n, int r);

    /**
     * Calcula el número de permutaciones posibles (nPr).
     * @param n Número total de elementos.
     * @param r Número de elementos seleccionados para permutación.
     * @return Número de permutaciones posibles.
     * @throws std::invalid_argument si n o r son negativos, o si r es mayor que n.
     * @throws std::overflow_error si el resultado excede el rango permitido de enteros.
     */
    static int permutation(int n, int r);
};

#endif // COMBINATORICS_H
