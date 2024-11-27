/*
    Archivo: file_io.mc
    Descripción: Ejemplo de operaciones de E/S de archivos en MC++.
    Propósito: Demostrar cómo leer y escribir archivos de forma segura y eficiente.
*/

IMPORTAR "file_utils"

// Función para leer el contenido de un archivo
FUNC leerArchivo(rutaArchivo: STRING): STRING {
    VAR contenido = file_utils.leerArchivo(rutaArchivo)
    RETORNAR contenido
}

// Función para escribir contenido en un archivo
FUNC escribirArchivo(rutaArchivo: STRING, contenido: STRING): BOOL {
    VAR resultado = file_utils.escribirArchivo(rutaArchivo, contenido)
    RETORNAR resultado
}

// Función para añadir contenido a un archivo existente
FUNC añadirAArchivo(rutaArchivo: STRING, contenido: STRING): BOOL {
    VAR resultado = file_utils.añadirAArchivo(rutaArchivo, contenido)
    RETORNAR resultado
}

// Función principal para ejecutar los ejemplos de E/S
FUNC main() {
    MOSTRAR("Ejemplo de operaciones de E/S de archivos en MC++...")

    // Ruta de archivo de ejemplo
    VAR ruta = "./datos/ejemplo.txt"

    // Escribir contenido en un archivo
    VAR contenidoEscribir = "Este es un ejemplo de escritura en archivo con MC++."
    SI escribirArchivo(ruta, contenidoEscribir) {
        MOSTRAR("Escritura exitosa en:", ruta)
    } MAS {
        MOSTRAR("Error al escribir en el archivo.")
    }

    // Leer contenido de un archivo
    VAR contenidoLeido = leerArchivo(ruta)
    SI contenidoLeido.NO_ES_VACIO() {
        MOSTRAR("Contenido leído del archivo:", contenidoLeido)
    } MAS {
        MOSTRAR("Error al leer el archivo o archivo vacío.")
    }

    // Añadir contenido a un archivo
    VAR contenidoAñadir = "\nAñadiendo esta línea al archivo existente."
    SI añadirAArchivo(ruta, contenidoAñadir) {
        MOSTRAR("Contenido añadido exitosamente.")
    } MAS {
        MOSTRAR("Error al añadir contenido al archivo.")
    }

    // Leer el archivo nuevamente para verificar el contenido añadido
    contenidoLeido = leerArchivo(ruta)
    MOSTRAR("Contenido final del archivo:", contenidoLeido)

    MOSTRAR("Ejemplo de operaciones de E/S de archivos completado.")
}
