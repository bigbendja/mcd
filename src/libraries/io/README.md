Aquí está la versión actualizada del archivo `README.md` para la librería `io` en MC++:

```markdown
# **Biblioteca de Entrada y Salida (`io`) - MC++ 1.0**

## **Descripción General**

La biblioteca `io` de MC++ ofrece un conjunto avanzado de herramientas para la gestión eficiente de archivos, captura de entrada de usuario y formato de salida profesional. Diseñada para entornos críticos y de alta demanda, `io` permite manejar archivos de gran tamaño, capturar entradas de manera segura y producir salidas estructuradas y personalizadas, asegurando un rendimiento óptimo y una experiencia de usuario fluida.

---

## **Características Principales**

1. **Gestión Avanzada de Archivos**:
   - Apertura, lectura, escritura, cierre y manipulación de archivos con manejo robusto de errores.
   - Soporte para archivos binarios y de texto en múltiples codificaciones.

2. **Entrada Segura y Flexible**:
   - Captura de datos numéricos, texto y contraseñas.
   - Validaciones avanzadas y tratamiento automático de excepciones.

3. **Formato de Salida Personalizado**:
   - Generación de salidas en JSON, tablas, alertas y logs.
   - Soporte para salida coloreada y estructurada.

4. **Configuración Adaptable**:
   - Ajustes dinámicos a través de archivos JSON (`io_config.json`) para personalizar rutas, permisos y políticas de manejo de archivos.

---

## **Instalación**

### **Requisitos Previos**

- **MC++ Core**: Versión 2.0 o superior.
- **Entorno de Desarrollo**:
  - Compilador compatible con C++17+.
  - Permisos adecuados para manipular archivos en el sistema.

### **Pasos de Instalación**

1. **Clonar el Repositorio**:
   ```bash
   git clone https://github.com/tuusuario/MCpp.git
   cd MCpp/src/io
   ```

2. **Compilación**:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Configuración Opcional**:
   Crea un archivo `io_config.json` en el directorio raíz para definir ajustes personalizados (ver sección de configuración).

---

## **Configuración**

La biblioteca permite personalizar su comportamiento mediante un archivo de configuración JSON. Ejemplo:

```json
{
  "default_path": "/var/log/mcpp",
  "permissions": "rw",
  "file_buffer_size": 8192,
  "default_encoding": "UTF-8",
  "log_output": true
}
```

### **Parámetros Principales**:
- **`default_path`**: Directorio predeterminado para operaciones de archivo.
- **`permissions`**: Permisos de archivo (`r` para lectura, `w` para escritura).
- **`file_buffer_size`**: Tamaño del búfer de lectura/escritura en bytes.
- **`default_encoding`**: Codificación predeterminada para archivos de texto.
- **`log_output`**: Habilita/deshabilita el registro de operaciones.

---

## **Uso de la Biblioteca**

### 1. **Gestión de Archivos**

**Abrir y Cerrar Archivos**
```mc++
VAR file = OPEN_FILE("/data/example.txt", "r");
CLOSE_FILE(file);
```

**Lectura y Escritura**
```mc++
VAR content = READ_FILE("/data/input.txt", 1024);
WRITE_FILE("/data/output.txt", "Contenido actualizado");
```

---

### 2. **Entrada de Usuario**

**Captura de Datos**
```mc++
VAR name = GET_INPUT("Introduce tu nombre:");
VAR age = GET_INT("Introduce tu edad (0-120):", 0, 120);
```

**Entrada Segura de Contraseñas**
```mc++
VAR password = GET_PASSWORD("Introduce tu contraseña:");
```

---

### 3. **Formato de Salida**

**Generar JSON**
```mc++
PRINT_JSON(MAP("status": "success", "message": "Operación completada"));
```

**Mostrar Tablas**
```mc++
PRINT_TABLE(LIST(
    LIST("Producto", "Cantidad"),
    LIST("Laptop", "5"),
    LIST("Teléfono", "10")
));
```

**Mensajes de Error**
```mc++
PRINT_ERROR("Error crítico al procesar el archivo.");
```

---

## **Pruebas**

El archivo `io_tests.cpp` incluye pruebas exhaustivas para validar la funcionalidad y estabilidad de la biblioteca. Ejecuta las pruebas con:

```bash
mc++ test io_tests.cpp
```

### **Ejemplo de Prueba**:
```cpp
void testReadFile() {
    VAR content = READ_FILE("/data/test_file.txt", 1024);
    ASSERT(content != "", "El archivo no debe estar vacío");
}
```

---

## **Buenas Prácticas**

1. **Optimización del Tamaño de Búfer**:
   - Ajusta `file_buffer_size` en `io_config.json` según el tamaño de los archivos procesados.
   
2. **Manejo de Excepciones**:
   - Usa bloques `TRY-CATCH` para capturar errores durante operaciones de entrada/salida.

3. **Ajustes Personalizados**:
   - Configura `default_path` y `default_encoding` para adaptarse al entorno específico.

---

## **Contribución**

La biblioteca `io` admite extensiones y mejoras por parte de la comunidad. Sigue estas pautas para contribuir:

1. **Estilo de Código**:
   - Adhiérete a los estándares de estilo definidos en la documentación de MC++.

2. **Pruebas**:
   - Incluye casos de prueba para cada nueva funcionalidad o mejora.

3. **Documentación**:
   - Actualiza el archivo `README.md` con información sobre los cambios propuestos.

---

## **Licencia**

La biblioteca `io` está protegida bajo una licencia propietaria. Consulta [LICENSE.md](../docs/LICENSE.md) para más información.

---

**Gracias por usar la biblioteca `io` en MC++.** Simplificando las operaciones de entrada y salida para sistemas avanzados.
```