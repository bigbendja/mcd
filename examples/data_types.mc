/*
    Archivo: data_types.mc
    Descripción: Ejemplo avanzado de manejo de tipos de datos en MC++.
    Propósito: Demostrar el uso de tipos de datos básicos y complejos en MC++ y sus operaciones.
*/

// Tipos de datos básicos y sus operaciones
FUNC operacionesBasicas() {
    VAR numeroEntero: INT = 42
    VAR numeroDecimal: FLOAT = 3.14159
    VAR texto: STRING = "MC++"
    VAR booleano: BOOL = VERDADERO

    MOSTRAR("Número Entero:", numeroEntero)
    MOSTRAR("Número Decimal:", numeroDecimal)
    MOSTRAR("Texto:", texto)
    MOSTRAR("Booleano:", booleano)

    // Operaciones aritméticas básicas
    VAR suma = numeroEntero + 10
    VAR producto = numeroDecimal * 2.0
    MOSTRAR("Suma de enteros:", suma)
    MOSTRAR("Producto de decimales:", producto)
}

// Uso de arrays
FUNC manejoArray() {
    VAR numeros: ARRAY<INT> = [1, 2, 3, 4, 5]
    MOSTRAR("Elementos del array:")
    PARA i DESDE 0 HASTA LONGITUD(numeros) {
        MOSTRAR(numeros[i])
    }
    // Modificación de un elemento
    numeros[2] = 10
    MOSTRAR("Array modificado:", numeros)
}

// Uso de mapas
FUNC manejoMapa() {
    VAR mapaEjemplo: MAP<STRING, INT> = {
        "uno": 1,
        "dos": 2,
        "tres": 3
    }
    MOSTRAR("Mapa original:", mapaEjemplo)

    // Agregar un nuevo par clave-valor
    mapaEjemplo["cuatro"] = 4
    MOSTRAR("Mapa actualizado:", mapaEjemplo)

    // Acceder a un valor por clave
    SI mapaEjemplo.HAS_KEY("dos") {
        MOSTRAR("Valor para la clave 'dos':", mapaEjemplo["dos"])
    }
}

// Uso de estructuras personalizadas
STRUCT Persona {
    nombre: STRING
    edad: INT
    profesion: STRING
}

FUNC ejemploEstructura() {
    VAR personaEjemplo: Persona = Persona("Ana", 30, "Ingeniera")
    MOSTRAR("Datos de la persona:")
    MOSTRAR("Nombre:", personaEjemplo.nombre)
    MOSTRAR("Edad:", personaEjemplo.edad)
    MOSTRAR("Profesión:", personaEjemplo.profesion)

    // Modificar un atributo
    personaEjemplo.edad = 31
    MOSTRAR("Edad actualizada:", personaEjemplo.edad)
}

// Función principal para ejecutar los ejemplos de tipos de datos
FUNC main() {
    MOSTRAR("Demostración de tipos de datos en MC++")

    MOSTRAR("\n--- Operaciones Básicas ---")
    operacionesBasicas()

    MOSTRAR("\n--- Manejo de Arrays ---")
    manejoArray()

    MOSTRAR("\n--- Manejo de Mapas ---")
    manejoMapa()

    MOSTRAR("\n--- Uso de Estructuras Personalizadas ---")
    ejemploEstructura()

    MOSTRAR("Demostración de tipos de datos completada.")
}
