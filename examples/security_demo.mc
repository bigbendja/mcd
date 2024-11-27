/*
    Archivo: security_demo.mc
    Descripción: Ejemplo de uso avanzado de la librería `security` en MC++ para funciones de seguridad de autenticación, monitoreo de acceso y encriptación de datos.
    Propósito: Mostrar cómo implementar medidas de seguridad proactivas y eficientes en MC++.
*/

IMPORTAR "security"

// Configuración inicial de seguridad
VAR intentosPermitidos = 3
VAR tiempoBloqueo = 300   // Tiempo en segundos

FUNC autenticarUsuario(usuario: STRING, contrasena: STRING): BOOL {
    SI (security.verificarCredenciales(usuario, contrasena)) {
        security.registrarAcceso(usuario, "Autenticación exitosa")
        MOSTRAR("Acceso concedido para " + usuario)
        RETORNAR VERDADERO
    } MÁS {
        security.registrarIntentoFallido(usuario)
        SI (security.obtenerIntentosFallidos(usuario) >= intentosPermitidos) {
            security.bloquearUsuario(usuario, tiempoBloqueo)
            MOSTRAR("Usuario " + usuario + " bloqueado por múltiples intentos fallidos.")
        } MÁS {
            MOSTRAR("Acceso denegado. Intento fallido.")
        }
        RETORNAR FALSO
    }
}

FUNC encriptarDatos(datos: STRING): STRING {
    VAR datosEncriptados = security.encriptar(datos, "AES-256")
    MOSTRAR("Datos encriptados exitosamente.")
    RETORNAR datosEncriptados
}

FUNC desencriptarDatos(datosEncriptados: STRING): STRING {
    VAR datosDesencriptados = security.desencriptar(datosEncriptados, "AES-256")
    MOSTRAR("Datos desencriptados exitosamente.")
    RETORNAR datosDesencriptados
}

FUNC monitoreoActividad() {
    MIENTRAS (TRUE) {
        security.detectarActividadesInusuales()
        SI (security.hayAlertaDeSeguridad()) {
            VAR alerta = security.obtenerUltimaAlerta()
            MOSTRAR("Alerta de Seguridad: " + alerta.mensaje)
            // Realiza las acciones necesarias en respuesta a la alerta
            security.tomarAccion(alerta)
        }
        ESPERAR(300)
    }
}

FUNC main() {
    MOSTRAR("Iniciando demostración de seguridad en MC++...")
    
    // Ejemplo de autenticación
    VAR usuario = "admin"
    VAR contrasena = "password123"
    autenticarUsuario(usuario, contrasena)

    // Ejemplo de encriptación y desencriptación de datos
    VAR datos = "Información Confidencial"
    VAR datosEncriptados = encriptarDatos(datos)
    VAR datosDesencriptados = desencriptarDatos(datosEncriptados)

    MOSTRAR("Datos Originales: " + datos)
    MOSTRAR("Datos Encriptados: " + datosEncriptados)
    MOSTRAR("Datos Desencriptados: " + datosDesencriptados)

    // Inicia el monitoreo de actividad en segundo plano
    monitoreoActividad()
}
