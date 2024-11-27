/*
    Archivo: control_structures.mc
    Descripción: Ejemplo avanzado de uso de estructuras de control en MC++.
    Propósito: Mostrar cómo utilizar condicionales, bucles y estructuras de control avanzadas para optimizar flujos de trabajo.
*/

// Función para verificar si un número es primo
FUNC esPrimo(numero: INT): BOOL {
    SI numero <= 1 {
        RETORNAR FALSO
    }
    PARA i DESDE 2 HASTA RAIZ(numero) INCREMENTO 1 {
        SI numero % i == 0 {
            RETORNAR FALSO
        }
    }
    RETORNAR VERDADERO
}

// Función para calcular el factorial de un número de manera recursiva
FUNC factorialRecursivo(n: INT): INT {
    SI n <= 1 {
        RETORNAR 1
    }
    RETORNAR n * factorialRecursivo(n - 1)
}

// Función para imprimir números de Fibonacci hasta un límite usando WHILE
FUNC imprimirFibonacci(limite: INT): VOID {
    VAR a = 0
    VAR b = 1
    VAR temp = 0
    MIENTRAS a <= limite {
        MOSTRAR(a)
        temp = a + b
        a = b
        b = temp
    }
}

// Ejemplo de estructura SWITCH para clasificación de edades
FUNC clasificarEdad(edad: INT): STRING {
    SELECCION edad {
        CASO edad <= 12:
            RETORNAR "Niño"
        CASO edad <= 19:
            RETORNAR "Adolescente"
        CASO edad <= 64:
            RETORNAR "Adulto"
        DEFECTO:
            RETORNAR "Mayor"
    }
}

// Función principal que utiliza diversas estructuras de control
FUNC main() {
    MOSTRAR("Demostración de estructuras de control en MC++")

    // Condicional IF
    VAR numero = 29
    SI esPrimo(numero) {
        MOSTRAR(numero, "es un número primo.")
    } SINO {
        MOSTRAR(numero, "no es un número primo.")
    }

    // Bucles FOR y WHILE
    MOSTRAR("Factorial de 5 usando recursión:", factorialRecursivo(5))
    MOSTRAR("Números de Fibonacci hasta 100:")
    imprimirFibonacci(100)

    // Estructura SWITCH
    VAR edad = 45
    MOSTRAR("Clasificación de edad:", clasificarEdad(edad))
    
    MOSTRAR("Ejecución de estructuras de control completada.")
}
