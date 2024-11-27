/*
    Archivo: basic_syntax.mc
    Descripción: Ejemplo básico de la sintaxis fundamental en MC++.
    Propósito: Proporcionar una visión general de la estructura y elementos básicos del lenguaje MC++.
*/

// Declaración de variables y tipos básicos
FUNC declaracionVariables() {
    VAR numeroEntero: INT = 10
    VAR numeroDecimal: FLOAT = 5.75
    VAR texto: STRING = "Hola, MC++"
    VAR booleano: BOOL = VERDADERO

    MOSTRAR("Número Entero:", numeroEntero)
    MOSTRAR("Número Decimal:", numeroDecimal)
    MOSTRAR("Texto:", texto)
    MOSTRAR("Booleano:", booleano)
}

// Control de flujo: Condicionales
FUNC ejemploCondicionales(valor: INT) {
    SI valor > 10 {
        MOSTRAR("El valor es mayor que 10.")
    } SINO SI valor == 10 {
        MOSTRAR("El valor es igual a 10.")
    } SINO {
        MOSTRAR("El valor es menor que 10.")
    }
}

// Control de flujo: Bucles
FUNC ejemploBucles() {
    // Bucle FOR
    MOSTRAR("Bucle FOR:")
    PARA i DESDE 1 HASTA 5 {
        MOSTRAR("Valor de i:", i)
    }

    // Bucle WHILE
    MOSTRAR("Bucle WHILE:")
    VAR contador = 1
    MIENTRAS contador <= 5 {
        MOSTRAR("Contador:", contador)
        contador = contador + 1
    }
}

// Funciones y parámetros
FUNC suma(a: INT, b: INT): INT {
    RETORNAR a + b
}

FUNC ejemploFunciones() {
    VAR resultado = suma(7, 3)
    MOSTRAR("Resultado de la suma:", resultado)
}

// Uso de arrays
FUNC ejemploArrays() {
    VAR numeros: ARRAY<INT> = [1, 2, 3, 4, 5]
    MOSTRAR("Elementos del array:")
    PARA i DESDE 0 HASTA LONGITUD(numeros) {
        MOSTRAR(numeros[i])
    }
}

// Función principal
FUNC main() {
    MOSTRAR("Ejemplo de Sintaxis Básica en MC++")

    MOSTRAR("\n--- Declaración de Variables ---")
    declaracionVariables()

    MOSTRAR("\n--- Condicionales ---")
    ejemploCondicionales(10)

    MOSTRAR("\n--- Bucles ---")
    ejemploBucles()

    MOSTRAR("\n--- Funciones ---")
    ejemploFunciones()

    MOSTRAR("\n--- Arrays ---")
    ejemploArrays()

    MOSTRAR("Ejemplo de sintaxis básica completado.")
}
