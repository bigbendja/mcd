#ifndef TEXT_TRANSFORMATION_H
#define TEXT_TRANSFORMATION_H

#include <string>

/**
 * @class TextTransformation
 * @brief Ofrece operaciones avanzadas para la transformación y manipulación de texto.
 *
 * Métodos útiles para cambiar el formato de cadenas, eliminar espacios, y convertir
 * a formatos específicos como `snake_case` o `kebab-case`.
 */
class TextTransformation {
public:
    /**
     * @brief Convierte todos los caracteres de una cadena a mayúsculas.
     * @param text Cadena de entrada.
     * @return Cadena con todos los caracteres en mayúsculas.
     */
    static std::string toUpper(const std::string& text);

    /**
     * @brief Convierte todos los caracteres de una cadena a minúsculas.
     * @param text Cadena de entrada.
     * @return Cadena con todos los caracteres en minúsculas.
     */
    static std::string toLower(const std::string& text);

    /**
     * @brief Capitaliza el primer carácter de una cadena.
     * @param text Cadena de entrada.
     * @return Cadena con el primer carácter en mayúscula y el resto en minúsculas.
     */
    static std::string capitalize(const std::string& text);

    /**
     * @brief Elimina los espacios al inicio y al final de la cadena.
     * @param text Cadena de entrada.
     * @return Cadena sin espacios en los extremos.
     */
    static std::string trim(const std::string& text);

    /**
     * @brief Elimina todos los espacios en blanco de una cadena.
     * @param text Cadena de entrada.
     * @return Cadena sin ningún espacio en blanco.
     */
    static std::string removeWhitespace(const std::string& text);

    /**
     * @brief Reemplaza todas las ocurrencias de un carácter en una cadena.
     * @param text Cadena de entrada.
     * @param target Carácter que se desea reemplazar.
     * @param replacement Carácter que reemplazará al objetivo.
     * @return Cadena con los caracteres reemplazados.
     */
    static std::string replaceChar(const std::string& text, char target, char replacement);

    /**
     * @brief Convierte una cadena a formato "Title Case" (cada palabra inicia con mayúscula).
     * @param text Cadena de entrada.
     * @return Cadena transformada a formato Title Case.
     */
    static std::string toTitleCase(const std::string& text);

    /**
     * @brief Convierte una cadena a formato "snake_case".
     * @param text Cadena de entrada.
     * @return Cadena convertida a snake_case.
     */
    static std::string toSnakeCase(const std::string& text);

    /**
     * @brief Convierte una cadena a formato "kebab-case".
     * @param text Cadena de entrada.
     * @return Cadena convertida a kebab-case.
     */
    static std::string toKebabCase(const std::string& text);
};

#endif // TEXT_TRANSFORMATION_H
