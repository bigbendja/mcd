/*
    Archivo: interop_example.mc
    Descripción: Ejemplo de interoperabilidad en MC++.
    Propósito: Demostrar cómo MC++ puede interactuar con otros lenguajes, como Python y C++, para operaciones multi-plataforma.
*/

IMPORTAR "interop"

// Definición de la ruta al script Python y archivo de C++
VAR rutaScriptPython = "./scripts/operaciones_avanzadas.py"
VAR rutaModuloCPP = "./modulos/operaciones_cpp.so"

// Función para invocar una función Python desde MC++
FUNC invocarPython(a: FLOAT, b: FLOAT): FLOAT {
    VAR resultadoPython = interop.llamarPython(rutaScriptPython, "calcularSuma", a, b)
    MOSTRAR("Resultado desde Python:", resultadoPython)
    RETORNAR resultadoPython
}

// Función para invocar una función de C++ desde MC++
FUNC invocarCPP(x: FLOAT, y: FLOAT): FLOAT {
    VAR resultadoCPP = interop.llamarCpp(rutaModuloCPP, "calcularMultiplicacion", x, y)
    MOSTRAR("Resultado desde C++:", resultadoCPP)
    RETORNAR resultadoCPP
}

// Ejemplo principal de interoperabilidad
FUNC main() {
    MOSTRAR("Iniciando ejemplo de interoperabilidad en MC++...")

    VAR valor1 = 12.5
    VAR valor2 = 7.3

    // Llamada a función Python
    VAR resultadoPython = invocarPython(valor1, valor2)

    // Llamada a función C++
    VAR resultadoCPP = invocarCPP(valor1, valor2)

    MOSTRAR("Resultado final (suma y multiplicación):", resultadoPython + resultadoCPP)
    MOSTRAR("Ejemplo de interoperabilidad completado.")
}
