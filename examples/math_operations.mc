/*
    Archivo: math_operations.mc
    Descripción: Ejemplo de operaciones matemáticas avanzadas en MC++.
    Propósito: Demostrar el uso de funciones matemáticas complejas en MC++ para cálculos de alto rendimiento.
*/

IMPORTAR "math"

// Definición de constantes matemáticas
VAR PI = 3.141592653589793
VAR E = 2.718281828459045

// Función para calcular el área de un círculo
FUNC calcularAreaCirculo(radio: FLOAT): FLOAT {
    RETORNAR math.multiplicar(PI, math.potencia(radio, 2))
}

// Función para calcular la raíz cuadrada de un valor
FUNC calcularRaizCuadrada(valor: FLOAT): FLOAT {
    RETORNAR math.raiz(valor)
}

// Función para resolver una ecuación cuadrática ax^2 + bx + c = 0
FUNC resolverEcuacionCuadratica(a: FLOAT, b: FLOAT, c: FLOAT): LIST {
    VAR discriminante = math.restar(math.potencia(b, 2), math.multiplicar(4, math.multiplicar(a, c)))
    SI (discriminante < 0) {
        MOSTRAR("La ecuación no tiene soluciones reales.")
        RETORNAR []
    }
    VAR raizDiscriminante = math.raiz(discriminante)
    VAR solucion1 = math.dividir(math.restar(-b, raizDiscriminante), 2 * a)
    VAR solucion2 = math.dividir(math.sumar(-b, raizDiscriminante), 2 * a)
    RETORNAR [solucion1, solucion2]
}

// Función principal para ejecutar los ejemplos
FUNC main() {
    MOSTRAR("Ejemplo de operaciones matemáticas en MC++...")

    // Cálculo de área de un círculo
    VAR radio = 5.0
    VAR areaCirculo = calcularAreaCirculo(radio)
    MOSTRAR("Área de un círculo con radio", radio, ":", areaCirculo)

    // Cálculo de raíz cuadrada
    VAR valor = 16.0
    VAR raizCuadrada = calcularRaizCuadrada(valor)
    MOSTRAR("Raíz cuadrada de", valor, ":", raizCuadrada)

    // Resolución de ecuación cuadrática
    VAR coefA = 1.0
    VAR coefB = -3.0
    VAR coefC = 2.0
    VAR soluciones = resolverEcuacionCuadratica(coefA, coefB, coefC)
    MOSTRAR("Soluciones de la ecuación cuadrática:", soluciones)

    MOSTRAR("Ejemplo de operaciones matemáticas completado.")
}
