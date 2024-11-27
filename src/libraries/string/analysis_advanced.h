#ifndef ANALYSIS_ADVANCED_H
#define ANALYSIS_ADVANCED_H

#include <string>
#include <map>

/**
 * Módulo Analysis Advanced en MC++:
 * Ofrece funciones avanzadas de análisis de cadenas para medir, comparar y extraer información clave.
 */

class AnalysisAdvanced {
public:
    /**
     * Obtiene la longitud de una cadena.
     * @param text Cadena de texto a analizar.
     * @return Longitud de la cadena.
     */
    static int length(const std::string& text);

    /**
     * Cuenta las ocurrencias de un subtexto dentro de una cadena.
     * @param text Texto principal donde buscar.
     * @param target Subtexto a contar.
     * @return Número de ocurrencias del subtexto.
     */
    static int countOccurrences(const std::string& text, const std::string& target);

    /**
     * Verifica si una cadena está vacía.
     * @param text Cadena de texto a verificar.
     * @return Verdadero si la cadena está vacía, falso en caso contrario.
     */
    static bool isEmpty(const std::string& text);

    /**
     * Verifica si una cadena comienza con un prefijo específico.
     * @param text Cadena de texto a verificar.
     * @param prefix Prefijo a buscar.
     * @return Verdadero si comienza con el prefijo, falso en caso contrario.
     */
    static bool startsWith(const std::string& text, const std::string& prefix);

    /**
     * Verifica si una cadena termina con un sufijo específico.
     * @param text Cadena de texto a verificar.
     * @param suffix Sufijo a buscar.
     * @return Verdadero si termina con el sufijo, falso en caso contrario.
     */
    static bool endsWith(const std::string& text, const std::string& suffix);

    /**
     * Verifica si una cadena contiene solo caracteres alfabéticos.
     * @param text Cadena de texto a verificar.
     * @return Verdadero si contiene solo letras, falso en caso contrario.
     */
    static bool containsOnlyAlpha(const std::string& text);

    /**
     * Verifica si una cadena contiene solo dígitos.
     * @param text Cadena de texto a verificar.
     * @return Verdadero si contiene solo dígitos, falso en caso contrario.
     */
    static bool containsOnlyDigits(const std::string& text);

    /**
     * Cuenta la cantidad de palabras en una cadena.
     * @param text Cadena de texto a analizar.
     * @return Número de palabras en el texto.
     */
    static int wordCount(const std::string& text);

    /**
     * Calcula la frecuencia de caracteres en una cadena.
     * @param text Cadena de texto a analizar.
     * @return Mapa con caracteres como clave y sus frecuencias como valores.
     */
    static std::map<char, int> charFrequency(const std::string& text);

    /**
     * Encuentra el primer carácter no repetido en una cadena.
     * @param text Cadena de texto a analizar.
     * @return Primer carácter no repetido o '\0' si no hay caracteres únicos.
     */
    static char findFirstNonRepeatedChar(const std::string& text);

    /**
     * Calcula la similitud de Jaccard entre dos cadenas basándose en palabras únicas.
     * @param str1 Primera cadena.
     * @param str2 Segunda cadena.
     * @return Similitud de Jaccard (valor entre 0 y 1).
     */
    static float jaccardSimilarity(const std::string& str1, const std::string& str2);
};

#endif // ANALYSIS_ADVANCED_H
