/*
    Archivo: ai_ml_basics.mc
    Descripción: Ejemplo de uso de capacidades básicas de IA y ML en MC++.
    Propósito: Implementar un modelo básico de aprendizaje supervisado para reconocimiento de patrones.
*/

IMPORTAR "ai_ml"

// Datos de entrenamiento (ejemplos simples de patrones)
VAR datosEntrenamiento = [
    {"entrada": [0, 0], "salida": 0},
    {"entrada": [0, 1], "salida": 1},
    {"entrada": [1, 0], "salida": 1},
    {"entrada": [1, 1], "salida": 0}
]

// Configuración del modelo de aprendizaje
VAR tasaAprendizaje = 0.1
VAR epocas = 1000

// Función para inicializar el modelo de aprendizaje
FUNC inicializarModelo() {
    VAR modelo = ai_ml.crearModelo("perceptron_simple")
    modelo.configurar("tasa_aprendizaje", tasaAprendizaje)
    modelo.configurar("epocas", epocas)
    RETORNAR modelo
}

// Función para entrenar el modelo con los datos de entrenamiento
FUNC entrenarModelo(modelo) {
    PARA CADA dato EN datosEntrenamiento {
        modelo.entrenar(dato.entrada, dato.salida)
    }
    MOSTRAR("Entrenamiento completado.")
}

// Función para probar el modelo con una entrada nueva
FUNC probarModelo(modelo, entrada: LISTA) {
    VAR resultado = modelo.predecir(entrada)
    MOSTRAR("Entrada: " + entrada + " -> Predicción: " + resultado)
    RETORNAR resultado
}

// Ejecución principal del ejemplo de IA/ML
FUNC main() {
    MOSTRAR("Iniciando ejemplo básico de IA/ML en MC++...")

    // Inicialización y entrenamiento del modelo
    VAR modelo = inicializarModelo()
    entrenarModelo(modelo)

    // Pruebas de predicción
    VAR pruebas = [
        [0, 0],
        [0, 1],
        [1, 0],
        [1, 1]
    ]

    PARA CADA prueba EN pruebas {
        probarModelo(modelo, prueba)
    }
}
