/*
    Archivo: string_manipulation.mc
    Descripción: Ejemplo de manipulación de cadenas en MC++.
    Propósito: Demostrar el uso de funciones avanzadas de procesamiento de texto en MC++.
*/

IMPORTAR "string_utils"

// Función para convertir una cadena a mayúsculas
FUNC convertirAMayusculas(cadena: STRING): STRING {
    RETORNAR string_utils.toUpper(cadena)
}

// Función para dividir una cadena en una lista de palabras
FUNC dividirEnPalabras(cadena: STRING): LIST {
    RETORNAR string_utils.split(cadena, ' ')
}

// Función para reemplazar todas las apariciones de una subcadena en una cadena
FUNC reemplazarSubcadena(cadena: STRING, buscar: STRING, reemplazar: STRING): STRING {
    RETORNAR string_utils.replaceAll(cadena, buscar, reemplazar)
}

// Función para eliminar espacios en blanco al principio y al final de una cadena
FUNC recortarEspacios(cadena: STRING): STRING {
    RETORNAR string_utils.trim(cadena)
}

// Función principal para ejecutar los ejemplos
FUNC main() {
    MOSTRAR("Ejemplo de manipulación de cadenas en MC++...")

    // Convertir a mayúsculas
    VAR texto = "mc++ es increíble"
    VAR textoMayusculas = convertirAMayusculas(texto)
    MOSTRAR("Convertir a mayúsculas:", textoMayusculas)

    // Dividir en palabras
    VAR oracion = "MC++ es un lenguaje de programación poderoso"
    VAR palabras = dividirEnPalabras(oracion)
    MOSTRAR("Dividir en palabras:", palabras)

    // Reemplazar subcadena
    VAR textoOriginal = "MC++ hace el desarrollo autónomo posible"
    VAR textoModificado = reemplazarSubcadena(textoOriginal, "autónomo", "eficiente")
    MOSTRAR("Reemplazar subcadena:", textoModificado)

    // Recortar espacios
    VAR textoConEspacios = "   MC++ optimiza el rendimiento   "
    VAR textoRecortado = recortarEspacios(textoConEspacios)
    MOSTRAR("Recortar espacios:", textoRecortado)

    MOSTRAR("Ejemplo de manipulación de cadenas completado.")
}
