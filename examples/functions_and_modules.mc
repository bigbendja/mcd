/*
    Archivo: functions_and_modules.mc
    Descripción: Ejemplo avanzado de definición y uso de funciones y módulos en MC++.
    Propósito: Mostrar la creación de módulos, funciones, parámetros, y cómo importar y utilizar módulos.
*/

// Definición del módulo `MatematicasAvanzadas`
MODULO MatematicasAvanzadas {
    // Función para calcular el factorial de un número
    FUNC factorial(n: INT): INT {
        VAR resultado = 1
        SI n < 0 {
            MOSTRAR("Error: el número debe ser no negativo.")
            RETORNAR -1
        }
        PARA i DESDE 1 HASTA n INCREMENTO 1 {
            resultado *= i
        }
        RETORNAR resultado
    }

    // Función para calcular el n-ésimo término de la secuencia de Fibonacci
    FUNC fibonacci(n: INT): INT {
        SI n <= 0 {
            RETORNAR 0
        } SI n == 1 {
            RETORNAR 1
        }
        VAR a = 0
        VAR b = 1
        VAR temp = 0
        PARA i DESDE 2 HASTA n INCREMENTO 1 {
            temp = a + b
            a = b
            b = temp
        }
        RETORNAR b
    }
}

// Definición del módulo `ConversorDeUnidades`
MODULO ConversorDeUnidades {
    CONST METROS_A_PIES = 3.28084
    CONST KILOGRAMOS_A_LIBRAS = 2.20462

    // Función para convertir metros a pies
    FUNC metrosAPies(metros: FLOAT): FLOAT {
        RETORNAR metros * METROS_A_PIES
    }

    // Función para convertir kilogramos a libras
    FUNC kilogramosALibras(kilogramos: FLOAT): FLOAT {
        RETORNAR kilogramos * KILOGRAMOS_A_LIBRAS
    }
}

// Función principal para demostrar el uso de funciones y módulos
FUNC main() {
    MOSTRAR("Ejemplo de uso de funciones y módulos en MC++")

    // Uso de funciones del módulo `MatematicasAvanzadas`
    IMPORTAR MatematicasAvanzadas

    VAR numero = 5
    MOSTRAR("Factorial de", numero, ":", MatematicasAvanzadas.factorial(numero))

    VAR terminoFibonacci = 10
    MOSTRAR("Décimo término de Fibonacci:", MatematicasAvanzadas.fibonacci(terminoFibonacci))

    // Uso de funciones del módulo `ConversorDeUnidades`
    IMPORTAR ConversorDeUnidades

    VAR metros = 10.0
    MOSTRAR(metros, "metros en pies:", ConversorDeUnidades.metrosAPies(metros))

    VAR kilogramos = 70.0
    MOSTRAR(kilogramos, "kilogramos en libras:", ConversorDeUnidades.kilogramosALibras(kilogramos))

    MOSTRAR("Demostración de funciones y módulos completada.")
}
