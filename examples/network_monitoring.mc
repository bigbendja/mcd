/*
    Archivo: network_monitoring.mc
    Descripción: Ejemplo de uso de la librería `monitoring` para monitoreo avanzado de red en MC++.
    Propósito: Implementar funciones de monitoreo de tráfico y latencia en tiempo real, con detección de anomalías y alertas.
*/

IMPORTAR "monitoring"

// Configuración inicial de parámetros de monitoreo
VAR max_bandwidth = 1000.0 // en Mbps
VAR max_latency = 200      // en milisegundos

FUNC monitorearTráficoRed() {
    VAR anchoBandaActual = monitoring.obtenerAnchoDeBanda()
    SI (anchoBandaActual > max_bandwidth) {
        monitoring.generarAlerta("Uso de ancho de banda crítico: " + anchoBandaActual + " Mbps")
        MOSTRAR("Alerta: Exceso en el uso de ancho de banda.")
    } MÁS {
        MOSTRAR("Ancho de banda actual: " + anchoBandaActual + " Mbps")
    }
}

FUNC monitorearLatenciaRed() {
    VAR latenciaActual = monitoring.obtenerLatencia()
    SI (latenciaActual > max_latency) {
        monitoring.generarAlerta("Latencia de red alta detectada: " + latenciaActual + " ms")
        MOSTRAR("Alerta: Latencia de red crítica.")
    } MÁS {
        MOSTRAR("Latencia actual: " + latenciaActual + " ms")
    }
}

FUNC monitoreoContinuo(intervalo: INT) {
    MIENTRAS (VERDADERO) {
        monitorearTráficoRed()
        monitorearLatenciaRed()
        
        // Detección de actividades inusuales
        SI (monitoring.hayActividadInusual()) {
            VAR alerta = monitoring.obtenerUltimaAlerta()
            MOSTRAR("Alerta detectada: " + alerta.mensaje)
            monitoring.tomarAccion(alerta)
        }
        ESPERAR(intervalo)
    }
}

FUNC main() {
    MOSTRAR("Iniciando monitoreo de red en MC++...")

    // Configura y comienza el monitoreo continuo de red
    VAR intervaloMonitoreo = 60  // en segundos
    monitoreoContinuo(intervaloMonitoreo)
}
