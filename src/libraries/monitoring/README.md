Aquí está la versión actualizada del archivo `README.md` para la librería `monitoring`:

```markdown
# **Librería de Monitoreo y Diagnóstico Avanzado (`monitoring`) - MC++ 1.0**

## **Descripción General**

La librería `monitoring` de MC++ proporciona capacidades avanzadas para supervisión y diagnóstico en tiempo real, siendo fundamental para aplicaciones críticas y entornos autónomos de alto rendimiento. Está diseñada para detectar condiciones críticas, registrar eventos clave y responder de manera proactiva mediante sistemas de alertas y notificaciones, todo mientras mantiene la eficiencia en el uso de los recursos.

---

## **Principales Funcionalidades**

### **1. Supervisión de Rendimiento (`performance_monitoring`)**
- **CPU y Memoria**:
  - Monitoriza el uso de recursos del sistema.
  - Activa escalado automático o alertas cuando los umbrales configurados son superados.
- **Tráfico de Red**:
  - Controla el ancho de banda utilizado y responde a picos de carga.
- **Temperatura del Sistema**:
  - Permite prevenir sobrecalentamientos mediante monitoreo en tiempo real.

### **2. Registro y Auditoría (`logging_audit`)**
- **Registro Detallado de Eventos**:
  - Incluye niveles como `INFO`, `WARNING`, `ERROR`, y `DEBUG`.
- **Auditoría de Operaciones**:
  - Realiza un seguimiento completo de eventos críticos para análisis post-mortem.

### **3. Gestión de Alertas y Notificaciones (`alerts_notifications`)**
- **Sistema de Alertas**:
  - Genera alertas automáticas basadas en umbrales.
  - Configuración flexible para envío de notificaciones por correo, SMS o webhooks.
- **Gestión Proactiva**:
  - Reintentos automáticos para notificaciones fallidas.
  - Confirmación de alertas por parte de usuarios autorizados.

---

## **Requisitos de Sistema**

- **MC++ Core**: Versión 2.0 o superior.
- **Compilador**: Compatible con C++17+.
- **Conexión a Internet**: Necesaria para notificaciones externas mediante webhooks o correo.

---

## **Instalación**

### **Paso 1: Clonar el Repositorio**
```bash
git clone https://github.com/tu_usuario/mc_monitoring.git
cd mc_monitoring
```

### **Paso 2: Configuración Inicial**
Ajusta los parámetros en el archivo `monitoring_config.json`:

```json
{
  "cpu_threshold": 0.85,
  "memory_threshold": 0.8,
  "network_max_bandwidth": 500.0,
  "notification_channels": {
    "email": "admin@tu_empresa.com",
    "sms": "+1234567890",
    "webhook": "https://tuwebhook.com/alerta"
  },
  "retention_policy": {
    "max_logs": 10000,
    "retention_period": 2592000
  }
}
```

### **Paso 3: Compilación**
Desde el directorio del proyecto:
```bash
mkdir build && cd build
cmake ..
make
```

### **Paso 4: Ejecución de Pruebas**
Ejecuta las pruebas unitarias para verificar la instalación:
```bash
ctest
```

---

## **Ejemplos de Uso**

### **1. Monitoreo de Recursos**

```cpp
#include "monitoring.h"

int main() {
    Monitoring monitor;
    monitor.monitorAndScaleCPU(0.85);  // Escala si la CPU supera el 85%.
    monitor.monitorAndAlertMemory(0.8);  // Genera alerta si la memoria supera el 80%.
    return 0;
}
```

### **2. Creación de Alertas Personalizadas**

```cpp
#include "monitoring.h"

int main() {
    Monitoring monitor;
    monitor.createAlert("NETWORK", "HIGH", "Tráfico de red elevado detectado");
    return 0;
}
```

### **3. Generación de Reportes de Auditoría**

```cpp
#include "monitoring.h"

int main() {
    Monitoring monitor;
    auto report = monitor.generateAuditReport();
    // Procesa el reporte como JSON o tabla
    return 0;
}
```

---

## **Configuración Personalizada**

- **Umbrales de Recursos**: Ajusta `cpu_threshold`, `memory_threshold`, y otros valores en `monitoring_config.json` para adaptarlos a las necesidades del sistema.
- **Canales de Notificación**: Configura `email`, `sms`, y `webhook` para asegurar alertas en tiempo real.
- **Política de Retención**:
  - `max_logs`: Número máximo de registros a mantener.
  - `retention_period`: Tiempo en segundos para mantener registros antiguos.

---

## **Pruebas Unitarias**

El archivo `monitoring_tests.cpp` incluye pruebas exhaustivas para validar las funciones principales. Ejecuta:
```bash
./run_tests
```

**Ejemplo de Prueba**:
```cpp
void testAlertCreation() {
    Monitoring monitor;
    monitor.createAlert("CPU", "CRITICAL", "Uso de CPU crítico");
    ASSERT_TRUE(monitor.alertExists("CPU", "CRITICAL"));
}
```

---

## **Buenas Prácticas**

1. **Optimización de Logs**:
   - Configura una política de retención adecuada para evitar consumo excesivo de almacenamiento.
2. **Validación de Alertas**:
   - Verifica que los canales de notificación estén activos antes de activar alertas críticas.
3. **Escalado Automático**:
   - Integra la librería con sistemas de escalado para prevenir interrupciones por sobrecarga.

---

## **Contribución**

Para contribuir:
1. Crea un _fork_ del repositorio.
2. Realiza los cambios y añade pruebas unitarias.
3. Envía un _pull request_ siguiendo las pautas descritas en `CONTRIBUTING.md`.

---

## **Licencia**

La librería `monitoring` está protegida bajo una licencia propietaria. Consulta el archivo `LICENSE` para más detalles.

---

**Gracias por usar la librería `monitoring` en MC++.** Garantiza un monitoreo autónomo y eficiente en tus sistemas críticos.
```