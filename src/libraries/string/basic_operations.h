#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include <string>
#include <vector>

/**
 * @class BasicOperations
 * @brief Proporciona operaciones fundamentales para manipulación de cadenas en MC++.
 */
class BasicOperations {
public:
    /**
     * @brief Concatena dos cadenas de texto.
     * @param str1 Primer string.
     * @param str2 Segundo string.
     * @return Cadena resultante de la concatenación.
     */
    static std::string concatenate(const std::string& str1, const std::string& str2);

    /**
     * @brief Obtiene una subcadena específica de un texto.
     * @param text Cadena base.
     * @param start Índice inicial (base 0) para extraer la subcadena.
     * @param length Cantidad de caracteres a extraer.
     * @return Subcadena extraída.
     * @throws std::out_of_range Si los índices están fuera del rango de la cadena.
     */
    static std::string substring(const std::string& text, int start, int length);

    /**
     * @brief Encuentra la posición de una subcadena dentro de un texto.
     * @param text Cadena donde buscar.
     * @param target Subcadena que se desea encontrar.
     * @param start Índice inicial para comenzar la búsqueda (opcional, por defecto 0).
     * @return Índice de la primera ocurrencia o -1 si no se encuentra.
     */
    static int indexOf(const std::string& text, const std::string& target, int start = 0);

    /**
     * @brief Reemplaza ocurrencias de una subcadena en un texto.
     * @param text Texto original.
     * @param oldSub Subcadena a reemplazar.
     * @param newSub Subcadena que reemplaza a oldSub.
     * @param count Número máximo de reemplazos (-1 para reemplazar todas las ocurrencias).
     * @return Texto modificado con los reemplazos.
     */
    static std::string replace(const std::string& text, const std::string& oldSub, const std::string& newSub, int count = -1);

    /**
     * @brief Divide una cadena en múltiples partes según un delimitador.
     * @param text Texto a dividir.
     * @param delimiter Delimitador que separa las partes.
     * @param maxSplits Número máximo de divisiones (-1 indica sin límite).
     * @return Vector con las partes obtenidas tras dividir el texto.
     * @throws std::invalid_argument Si el delimitador está vacío.
     */
    static std::vector<std::string> split(const std::string& text, const std::string& delimiter, int maxSplits = -1);

    /**
     * @brief Une un conjunto de cadenas en una sola, separadas por un delimitador.
     * @param elements Vector de cadenas a unir.
     * @param delimiter Cadena que separa cada elemento.
     * @return Cadena resultante tras la unión.
     */
    static std::string join(const std::vector<std::string>& elements, const std::string& delimiter);

    /**
     * @brief Invierte el orden de los caracteres en una cadena.
     * @param text Texto a invertir.
     * @return Cadena invertida.
     */
    static std::string reverse(const std::string& text);

    /**
     * @brief Cuenta las ocurrencias de un carácter en una cadena.
     * @param text Texto donde contar las ocurrencias.
     * @param charToCount Carácter a buscar.
     * @return Número de veces que aparece el carácter.
     */
    static int countChar(const std::string& text, char charToCount);
};

#endif // BASIC_OPERATIONS_H
