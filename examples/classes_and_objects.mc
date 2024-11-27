/*
    Archivo: classes_and_objects.mc
    Descripción: Ejemplo de uso de clases y objetos en MC++.
    Propósito: Mostrar la definición de clases, constructores, métodos y la creación de instancias.
*/

IMPORTAR "utils"

// Definición de la clase básica `Persona`
CLASE Persona {
    PRIVADO:
        VAR nombre: STRING
        VAR edad: INT

    PÚBLICO:
        // Constructor de la clase `Persona`
        CONSTRUCTOR(nombreInicial: STRING, edadInicial: INT) {
            nombre = nombreInicial
            edad = edadInicial
        }

        // Método para mostrar información de la persona
        FUNC mostrarInfo(): VOID {
            MOSTRAR("Nombre:", nombre, "| Edad:", edad)
        }

        // Método para cambiar la edad de la persona
        FUNC actualizarEdad(nuevaEdad: INT): VOID {
            SI nuevaEdad > 0 {
                edad = nuevaEdad
            } MAS {
                MOSTRAR("Edad no válida.")
            }
        }

        // Método para obtener el nombre de la persona
        FUNC obtenerNombre(): STRING {
            RETORNAR nombre
        }
}

// Clase `Estudiante`, que hereda de `Persona`
CLASE Estudiante : Persona {
    PRIVADO:
        VAR grado: STRING
        VAR promedio: FLOAT

    PÚBLICO:
        // Constructor de la clase `Estudiante`, que llama al constructor de `Persona`
        CONSTRUCTOR(nombreInicial: STRING, edadInicial: INT, gradoInicial: STRING, promedioInicial: FLOAT)
            : Persona(nombreInicial, edadInicial) {
            grado = gradoInicial
            promedio = promedioInicial
        }

        // Método para mostrar información completa del estudiante
        FUNC mostrarInfoCompleta(): VOID {
            mostrarInfo()  // Llama al método `mostrarInfo` de la clase base `Persona`
            MOSTRAR("Grado:", grado, "| Promedio:", promedio)
        }

        // Método para actualizar el promedio
        FUNC actualizarPromedio(nuevoPromedio: FLOAT): VOID {
            SI nuevoPromedio >= 0.0 Y nuevoPromedio <= 10.0 {
                promedio = nuevoPromedio
            } MAS {
                MOSTRAR("Promedio no válido.")
            }
        }
}

// Función principal para demostrar el uso de clases y objetos
FUNC main() {
    MOSTRAR("Ejemplo de uso de clases y objetos en MC++")

    // Crear una instancia de `Persona`
    VAR persona1 = Persona("Ana", 30)
    persona1.mostrarInfo()

    // Actualizar la edad de la persona
    persona1.actualizarEdad(31)
    MOSTRAR("Edad actualizada de", persona1.obtenerNombre(), ":")
    persona1.mostrarInfo()

    // Crear una instancia de `Estudiante`
    VAR estudiante1 = Estudiante("Juan", 20, "Ingeniería", 8.5)
    estudiante1.mostrarInfoCompleta()

    // Actualizar el promedio del estudiante
    estudiante1.actualizarPromedio(9.0)
    MOSTRAR("Promedio actualizado del estudiante:")
    estudiante1.mostrarInfoCompleta()

    MOSTRAR("Demostración de clases y objetos completada.")
}
