Aquí tienes la actualización del archivo `README.md` de la librería `utils` con la licencia más restrictiva, la Licencia de Propietario de Derechos (Proprietary License), que impide su distribución, modificación o uso sin el permiso explícito del titular de los derechos.

---

```markdown
# Librería `utils` - MC++ 1.0

La librería `utils` de MC++ proporciona herramientas avanzadas para la manipulación de archivos, operaciones de cadena de texto, registro de eventos (logging), y gestión de configuraciones. Estas utilidades son fundamentales para aplicaciones de MC++ que requieren manejo eficiente de datos, almacenamiento confiable y soporte para auditorías.

## Contenido

1. **FileUtils**: Funciones para operaciones avanzadas de archivos, como lectura, escritura, y manejo de archivos de log.
2. **StringUtils**: Herramientas para manipulación de cadenas, incluyendo operaciones de conversión de caso, división, y formateo de precisión.
3. **Logger**: Módulo de registro que permite log de eventos, mensajes de advertencia y errores, con soporte de rotación de archivos.
4. **Config**: Sistema de configuración basado en JSON que permite cargar y gestionar parámetros críticos de la aplicación.

## Instalación y Configuración

1. Clona el repositorio de MC++.
2. Asegúrate de que las dependencias estándar de C++ están instaladas.
3. Configura el archivo JSON `utils_config.json` en la carpeta `config`, ajustando los valores necesarios para tu entorno.

   ```json
   {
       "log_settings": {
           "log_level": "INFO",
           "log_file_path": "./logs/utils_log.txt",
           "max_log_file_size": 1048576,
           "log_rotation": true,
           "log_rotation_max_files": 5
       },
       "file_utils": {
           "default_file_path": "./data",
           "max_file_size": 5242880,
           "file_encoding": "UTF-8"
       },
       "string_utils": {
           "default_case": "lower",
           "trim_whitespace": true
       },
       "performance_settings": {
           "enable_optimizations": true,
           "cache_size_limit_mb": 50,
           "cache_eviction_policy": "LRU"
       }
   }
   ```

## Uso

### 1. `FileUtils` - Gestión de Archivos
   - **Lectura de Archivos**: `FileUtils::readFile("ruta_del_archivo");`
   - **Escritura en Archivos**: `FileUtils::writeFile("ruta_del_archivo", "contenido");`
   - **Añadir Contenido a Archivos**: `FileUtils::appendToFile("ruta_del_archivo", "contenido");`

### 2. `StringUtils` - Manipulación de Cadenas
   - **Conversión a Minúsculas**: `StringUtils::toLower("TEXTO");`
   - **División de Cadenas**: `StringUtils::split("texto1,texto2,texto3", ',');`
   - **Formateo de Precisión**: `StringUtils::toStringWithPrecision(3.14159, 2); // "3.14"`

### 3. `Logger` - Registro de Eventos
   - **Configurar Nivel de Log**: `Logger::setLogLevel("INFO");`
   - **Registrar Información**: `Logger::logInfo("Mensaje informativo");`
   - **Registrar Errores**: `Logger::logError("Mensaje de error");`

### 4. `Config` - Configuración de la Aplicación
   - **Cargar Configuración**: `Config::loadConfig("./config/utils_config.json");`
   - **Obtener Parámetro**: `Config::getSetting<std::string>("log_settings.log_level");`

## Ejecución de Pruebas

El archivo de pruebas `utils_tests.cpp` incluye pruebas unitarias para cada módulo de la librería `utils`.

Para compilar y ejecutar las pruebas:

```bash
g++ utils_tests.cpp -o utils_tests
./utils_tests
```

## Contribución

1. Crea un *fork* del repositorio.
2. Realiza las modificaciones en una nueva rama.
3. Envía un *pull request* con una descripción detallada de los cambios propuestos.

## Licencia

**Este software es propiedad exclusiva del titular de los derechos.**

No se permite su distribución, copia, modificación, o uso sin el permiso explícito del propietario. Cualquier violación de estos términos puede resultar en acciones legales. Para obtener autorización de uso o distribución, por favor contacta al propietario de los derechos de MC++.

---

La librería `utils` es una colección esencial para MC++ que asegura un manejo robusto y eficiente de datos, manteniendo un alto nivel de rendimiento y confiabilidad para aplicaciones críticas.
```

Este `README.md` ahora refleja la licencia más restrictiva, impidiendo el uso sin autorización y asegurando protección completa sobre los derechos de la librería `utils`.