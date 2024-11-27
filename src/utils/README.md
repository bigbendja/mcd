# Utils Library - MC++

La librería `utils` en MC++ proporciona una serie de utilidades esenciales que facilitan la gestión de archivos, manipulación de cadenas, registro de logs y configuración en tiempo de ejecución. Estas funcionalidades están diseñadas para ser eficientes, avanzadas y alineadas con los estándares profesionales de MC++, optimizando la experiencia de desarrollo en sistemas autónomos y de alto rendimiento.

---

## Contenidos

1. [Descripción General](#descripción-general)
2. [Instalación](#instalación)
3. [Dependencias](#dependencias)
4. [Uso](#uso)
5. [Archivos](#archivos)
6. [Configuración](#configuración)
7. [Ejemplos](#ejemplos)
8. [Pruebas Unitarias](#pruebas-unitarias)

---

## Descripción General

Esta biblioteca incluye los siguientes módulos:

- **File Utils**: Utilidades para operaciones avanzadas de archivos.
- **String Utils**: Funciones para manipulación avanzada de cadenas.
- **Logger**: Sistema de registro de logs configurable y detallado para auditoría y seguimiento de eventos.
- **Config**: Gestor de configuración dinámica que carga y aplica ajustes desde archivos JSON.

---

## Instalación

Para instalar y utilizar esta biblioteca, añade los archivos de `utils` a tu proyecto de MC++ y asegúrate de incluir las rutas de cabecera necesarias en el compilador. 

```sh
# Compilación típica de un archivo de prueba
mc++ -I./path_to_utils -o utils_test utils_tests.cpp
```

---

## Dependencias

Esta biblioteca depende de las siguientes librerías de MC++:
- `mc++/core` para el sistema base.
- `json` para la gestión de configuraciones en formato JSON (utilizado en el módulo `Config`).
  
---

## Uso

### 1. File Utils

Este módulo proporciona funciones para manipulación avanzada de archivos:
- `OpenFile`: Abre y gestiona archivos en modos específicos.
- `ReadFile`, `WriteFile`: Lectura y escritura optimizadas.
  
### 2. String Utils

Incluye utilidades para manipulación avanzada de cadenas de texto:
- `Trim`: Elimina espacios innecesarios.
- `ToUpper`, `ToLower`: Cambia el caso de caracteres en cadenas.

### 3. Logger

Sistema avanzado de logs con soporte para niveles de severidad (`INFO`, `WARNING`, `ERROR`) y salida configurable. Asegura el registro de eventos críticos para auditoría y diagnóstico:
- `LogInfo`, `LogWarning`, `LogError`: Registra mensajes de diferentes niveles de importancia.
- Configuración adicional en el archivo JSON `utils_config.json`.

### 4. Config

Permite cargar y gestionar configuraciones desde un archivo JSON. Facilita la personalización de ajustes en tiempo de ejecución, adaptando el sistema a diferentes entornos sin necesidad de recompilación:
- `LoadConfig`: Carga configuraciones del archivo `utils_config.json`.
- `GetConfigValue`: Accede a valores específicos configurados.

---

## Archivos

El directorio `utils` contiene los siguientes archivos:

- `file_utils.h`, `file_utils.cpp`: Funciones avanzadas para manipulación de archivos.
- `string_utils.h`, `string_utils.cpp`: Funciones para manipulación de cadenas.
- `logger.h`, `logger.cpp`: Sistema de registro de eventos y logs.
- `config.h`, `config.cpp`: Módulo de configuración que permite la carga de ajustes desde archivos JSON.
- `utils_config.json`: Archivo JSON para la configuración del sistema de logs y otros parámetros.
- `utils_tests.cpp`: Archivo de pruebas unitarias para los módulos de `utils`.

---

## Configuración

La configuración se gestiona mediante el archivo `utils_config.json`, donde se pueden definir:
- **Niveles de Log**: Configura el nivel de severidad de logs.
- **Rutas de archivos**: Define rutas para almacenamiento de logs y archivos temporales.
- **Parámetros adicionales**: Valores personalizados para adaptarse a diferentes entornos.

---

## Ejemplos

```mc++
// Ejemplo de uso del Logger
INCLUDE "logger.h";

FUNC main() {
    LogInfo("Inicio del sistema");
    LogWarning("Memoria disponible baja");
    LogError("Error crítico en el sistema");
}

// Ejemplo de Config
INCLUDE "config.h";

FUNC main() {
    LoadConfig("utils_config.json");
    VAR log_level = GetConfigValue("log_level");
}
```

---

## Pruebas Unitarias

Para validar el correcto funcionamiento de cada módulo, ejecuta el archivo `utils_tests.cpp`, que incluye pruebas unitarias de todos los módulos y asegura que cumplan con los requisitos de calidad de MC++.

```sh
# Ejecución de pruebas unitarias
mc++ -I./path_to_utils -o utils_test utils_tests.cpp
./utils_test
```

---

## Licencia

Esta librería está licenciada bajo Licencia propietario. Para más detalles, consulta el archivo `LICENSE`.

```
