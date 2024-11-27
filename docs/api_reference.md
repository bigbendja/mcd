# Referencia de API de MC++

Este documento proporciona una descripción técnica detallada de la API de MC++ y sus funciones principales. Organizado por módulos, esta referencia está diseñada para ayudar a los desarrolladores a construir sistemas autónomos y optimizados utilizando MC++.

---

## Tabla de Contenidos

1. [Librería de Monitoreo y Diagnóstico (`monitoring`)](#monitoring)
2. [Librería de Optimización Adaptativa (`adaptive_optimization`)](#adaptive_optimization)
3. [Librería de Inteligencia Artificial y Machine Learning (`ai_ml`)](#ai_ml)
4. [Librería de Interoperabilidad Multi-Lenguaje (`interop`)](#interop)
5. [Librería de Entrada y Salida (`io`)](#io)
6. [Librería Matemática (`math`)](#math)
7. [Librería de Seguridad y Auditoría (`security`)](#security)
8. [Librería de Optimización Interna (`self_optimization`)](#self_optimization)
9. [Librería de Manipulación de Cadenas (`string`)](#string)
10. [Librería de Utilidades Generales (`utils`)](#utils)
11. [Librería de Logging Avanzado (`logger`)](#logger)

---

## 1. Librería de Monitoreo y Diagnóstico (`monitoring`)

La librería `monitoring` permite supervisar, diagnosticar y responder a métricas del sistema en tiempo real, integrándose con otras librerías para garantizar el rendimiento óptimo.

### Funciones Principales

- **`monitorResourceUsage`**
  - **Descripción**: Supervisa el uso de recursos como CPU y memoria.
  - **Parámetros**: 
    - `resourceType` (`STRING`): Tipo de recurso a monitorizar.
  - **Retorno**: Mapa (`MAP`) con los detalles del recurso monitorizado, como porcentaje de uso y disponibilidad.

```cpp
MAP resourceData = monitorResourceUsage("CPU");
if (resourceData["usage"] > 85) {
    Logger::logWarning("CPU está por encima del 85%");
}
```

- **`alertThreshold`**
  - **Descripción**: Configura alertas basadas en límites predefinidos de recursos.
  - **Parámetros**:
    - `threshold` (`FLOAT`): Límite en porcentaje.
    - `resourceType` (`STRING`): Recurso a monitorizar.
  - **Retorno**: `BOOL` indicando si la configuración fue exitosa.

```cpp
bool success = alertThreshold(90, "MEMORY");
if (!success) {
    Logger::logError("No se pudo configurar el umbral de alerta para la memoria.");
}
```

### Relación con Otras Librerías

- **`logger`**: Para registrar eventos y alertas derivadas de métricas monitorizadas.
- **`adaptive_optimization`**: Utiliza los datos monitorizados para optimizar dinámicamente los recursos.

---

## 2. Librería de Optimización Adaptativa (`adaptive_optimization`)

La librería `adaptive_optimization` está diseñada para ajustar dinámicamente los recursos del sistema en función de métricas en tiempo real y patrones de uso predecibles.

### Funciones Principales

- **`dynamicLoadBalance`**
  - **Descripción**: Distribuye cargas de trabajo entre nodos disponibles basándose en el estado actual de los recursos.
  - **Parámetros**: 
    - `nodes` (`LIST`): Lista de nodos disponibles.
    - `process` (`STRING`): Nombre del proceso a asignar.
  - **Retorno**: Nombre del nodo (`STRING`) al que se asignó la carga.

```cpp
STRING nodoAsignado = dynamicLoadBalance(["Nodo1", "Nodo2", "Nodo3"], "ProcesoPrincipal");
Logger::logInfo("Proceso asignado a: " + nodoAsignado);
```

- **`smartResourceRelease`**
  - **Descripción**: Libera automáticamente recursos inactivos o subutilizados para maximizar la disponibilidad.
  - **Parámetros**:
    - `thresholdTime` (`INT`): Tiempo en segundos antes de liberar el recurso.
    - `resourceType` (`STRING`): Tipo de recurso a gestionar.
  - **Retorno**: Número de recursos liberados (`INT`).

```cpp
int recursosLiberados = smartResourceRelease(300, "MEMORY");
Logger::logInfo(to_string(recursosLiberados) + " recursos liberados.");
```

### Mejores Prácticas

1. Configurar umbrales precisos en `monitoring` para que `dynamicLoadBalance` sea más eficiente.
2. Integrar esta librería con `ai_ml` para optimizaciones basadas en aprendizaje automático.

### Relación con Otras Librerías

- **`monitoring`**: Proporciona las métricas necesarias para la optimización.
- **`logger`**: Registra las operaciones de balanceo y liberación de recursos.

---

## 3. Librería de Inteligencia Artificial y Machine Learning (`ai_ml`)

La librería `ai_ml` proporciona herramientas para entrenar modelos, realizar predicciones y optimizar sistemas mediante técnicas de aprendizaje automático.

### Funciones Principales

- **`trainModel`**
  - **Descripción**: Entrena un modelo de machine learning utilizando los datos proporcionados.
  - **Parámetros**:
    - `data` (`LIST`): Datos de entrenamiento.
    - `modelType` (`STRING`): Tipo de modelo (regresión, clasificación).
  - **Retorno**: Objeto del modelo entrenado.

```cpp
Model modelo = trainModel(dataset, "regression");
Logger::logInfo("Modelo entrenado con éxito.");
```

- **`predict`**
  - **Descripción**: Realiza predicciones utilizando un modelo entrenado.
  - **Parámetros**:
    - `model` (`OBJETO`): Modelo previamente entrenado.
    - `inputData` (`MAP`): Datos de entrada.
  - **Retorno**: Resultado de la predicción (`FLOAT` o `STRING`).

```cpp
FLOAT prediccion = predict(modelo, {{"feature1", 0.5}, {"feature2", 0.8}});
Logger::logInfo("Predicción realizada: " + to_string(prediccion));
```

### Relación con Otras Librerías

- **`adaptive_optimization`**: Utiliza predicciones para optimizar recursos.
- **`monitoring`**: Alimenta métricas para entrenar modelos y realizar predicciones.

---

## 4. Librería de Interoperabilidad Multi-Lenguaje (`interop`)

La librería `interop` permite la interacción entre MC++ y otros lenguajes, como Python y C++, para extender las capacidades del sistema.

### Funciones Principales

- **`executePythonScript`**
  - **Descripción**: Ejecuta un script Python desde MC++.
  - **Parámetros**:
    - `scriptPath` (`STRING`): Ruta del script.
    - `arguments` (`MAP`): Argumentos a pasar.
  - **Retorno**: Salida del script (`STRING`).

```mc++
IMPORT "python_interface" AS py;

FUNC ejecutar_script(): VOID {
    py.executePythonScript("script.py", {"arg1": "valor1"});
}
```

- **`callCppFunction`**
  - **Descripción**: Llama a una función definida en C++ desde MC++.
  - **Parámetros**:
    - `functionName` (`STRING`): Nombre de la función.
    - `args` (`LIST`): Argumentos.
  - **Retorno**: Resultado de la función (`STRING` o `FLOAT`).

```mc++
IMPORT "cpp_interface" AS cpp;

FUNC llamar_cpp(): VOID {
    cpp.callCppFunction("miFuncion", [1, 2, 3]);
}
```

### Mejores Prácticas

1. Asegurar que las dependencias externas estén correctamente configuradas antes de la interoperabilidad.
2. Utilizar `logger` para registrar fallos de integración.

---

## 5. Librería de Entrada y Salida (`io`)

La librería `io` permite la gestión eficiente de archivos y flujos de datos en MC++.

### Funciones Principales

- **`readFile`**
  - **Descripción**: Lee el contenido de un archivo.
  - **Parámetros**:
    - `filePath` (`STRING`): Ruta del archivo.
  - **Retorno**: Contenido como `STRING`.

```cpp
STRING contenido = readFile("archivo.txt");
Logger::logInfo("Contenido leído: " + contenido);
```

- **`writeToFile`**
  - **Descripción**: Escribe datos en un archivo.
  - **Parámetros**:
    - `filePath` (`STRING`): Ruta del archivo.
    - `data` (`STRING`): Datos a escribir.
  - **Retorno**: `BOOL` indicando éxito.

```cpp
bool success = writeToFile("salida.txt", "Datos importantes.");
if (success) {
    Logger::logInfo("Datos escritos correctamente.");
}
```

```markdown
## 6. Librería Matemática (`math`)

La librería `math` ofrece operaciones avanzadas para cálculos matemáticos, incluyendo álgebra lineal, combinatoria y análisis trigonométrico.

### Funciones Principales

- **`calculateDeterminant`**
  - **Descripción**: Calcula el determinante de una matriz.
  - **Parámetros**:
    - `matrix` (`LIST` de `LIST`): Matriz a analizar.
  - **Retorno**: Determinante como `FLOAT`.

```cpp
FLOAT determinante = calculateDeterminant({{1, 2}, {3, 4}});
Logger::logInfo("Determinante calculado: " + to_string(determinante));
```

- **`solveLinearEquation`**
  - **Descripción**: Resuelve un sistema de ecuaciones lineales.
  - **Parámetros**:
    - `coefficients` (`LIST`): Coeficientes del sistema.
    - `constants` (`LIST`): Términos independientes.
  - **Retorno**: Soluciones como `LIST`.

```cpp
LIST soluciones = solveLinearEquation({{2, 1}, {1, -1}}, {5, -1});
Logger::logInfo("Soluciones del sistema: " + to_string(soluciones));
```

### Relación con Otras Librerías

- **`ai_ml`**: Utiliza operaciones matemáticas para optimizar modelos.
- **`adaptive_optimization`**: Aplica cálculos avanzados para el balanceo dinámico.

---

## 7. Librería de Seguridad y Auditoría (`security`)

La librería `security` proporciona herramientas avanzadas para garantizar la integridad del sistema y la protección de datos.

### Funciones Principales

- **`encryptData`**
  - **Descripción**: Cifra datos sensibles utilizando algoritmos seguros.
  - **Parámetros**:
    - `data` (`STRING`): Datos a cifrar.
    - `key` (`STRING`): Clave de cifrado.
  - **Retorno**: Datos cifrados (`STRING`).

```cpp
STRING datosCifrados = encryptData("clave_secreta", "Datos importantes.");
Logger::logInfo("Datos cifrados correctamente.");
```

- **`authenticateUser`**
  - **Descripción**: Verifica las credenciales de un usuario.
  - **Parámetros**:
    - `username` (`STRING`): Nombre de usuario.
    - `password` (`STRING`): Contraseña.
  - **Retorno**: `BOOL` indicando éxito o fallo.

```cpp
bool autenticado = authenticateUser("usuario", "contraseña123");
if (!autenticado) {
    Logger::logError("Error de autenticación para el usuario.");
}
```

- **`logEvent`**
  - **Descripción**: Registra un evento crítico en el sistema de auditoría.
  - **Parámetros**:
    - `event` (`STRING`): Mensaje del evento.
    - `level` (`ENUM: INFO | WARNING | CRITICAL`): Nivel del evento.
  - **Retorno**: `VOID`.

```cpp
AuditManager::logEvent("Intento de acceso no autorizado", AuditManager::EventLevel::CRITICAL);
```

---

## 8. Librería de Optimización Interna (`self_optimization`)

La librería `self_optimization` permite que el sistema ajuste automáticamente sus parámetros para maximizar el rendimiento.

### Funciones Principales

- **`autoAdjustParameters`**
  - **Descripción**: Ajusta parámetros del sistema automáticamente.
  - **Parámetros**:
    - `systemMetrics` (`MAP`): Métricas actuales del sistema.
  - **Retorno**: `BOOL` indicando éxito o fallo.

```cpp
bool ajusteExitoso = autoAdjustParameters({{"CPU", 85}, {"MEMORY", 70}});
Logger::logInfo("Parámetros ajustados automáticamente.");
```

- **`optimizeRuntime`**
  - **Descripción**: Optimiza el tiempo de ejecución de procesos basándose en métricas y patrones históricos.
  - **Parámetros**:
    - `metrics` (`MAP`): Métricas actuales.
  - **Retorno**: `STRING` con detalles de la optimización.

```cpp
STRING detallesOptimizacion = optimizeRuntime({{"latency", 30}, {"throughput", 500}});
Logger::logInfo("Optimización completa: " + detallesOptimizacion);
```

---

## 9. Librería de Manipulación de Cadenas (`string`)

La librería `string` facilita operaciones avanzadas para manipulación y análisis de texto.

### Funciones Principales

- **`toLower`**
  - **Descripción**: Convierte una cadena a minúsculas.
  - **Parámetros**:
    - `text` (`STRING`): Cadena de entrada.
  - **Retorno**: Cadena convertida (`STRING`).

```cpp
STRING textoMinusculas = toLower("MC++ ES INCREÍBLE");
Logger::logInfo("Texto convertido a minúsculas: " + textoMinusculas);
```

- **`replaceAll`**
  - **Descripción**: Reemplaza todas las ocurrencias de un patrón en una cadena.
  - **Parámetros**:
    - `text` (`STRING`): Texto original.
    - `pattern` (`STRING`): Patrón a reemplazar.
    - `replacement` (`STRING`): Texto de reemplazo.
  - **Retorno**: Texto modificado (`STRING`).

```cpp
STRING textoReemplazado = replaceAll("MC++ es MC++", "MC++", "Machine Code++");
Logger::logInfo("Texto modificado: " + textoReemplazado);
```

---

## 10. Librería de Utilidades Generales (`utils`)

La librería `utils` contiene herramientas generales para facilitar el desarrollo y la configuración del sistema.

### Funciones Principales

- **`logEvent`**
  - **Descripción**: Registra un evento en el archivo de log.
  - **Parámetros**:
    - `message` (`STRING`): Mensaje a registrar.
  - **Retorno**: `VOID`.

```cpp
Logger::logEvent("Iniciando el sistema.");
```

- **`loadConfig`**
  - **Descripción**: Carga configuraciones desde un archivo.
  - **Parámetros**:
    - `filePath` (`STRING`): Ruta del archivo de configuración.
  - **Retorno**: Configuraciones cargadas como `MAP`.

```cpp
MAP configuraciones = loadConfig("config.json");
Logger::logInfo("Configuraciones cargadas.");
```

---

## 11. Librería de Logging Avanzado (`logger`)

### Funciones Principales

- **`initialize`**
  - **Descripción**: Configura el sistema de logging.
  - **Parámetros**:
    - `file_path` (`STRING`): Ruta del archivo.
    - `level` (`ENUM: INFO | DEBUG | WARNING | ERROR | CRITICAL`): Nivel mínimo de log.

```cpp
Logger::initialize("sistema_log.txt", Logger::LogLevel::INFO);
```

- **`log`**
  - **Descripción**: Registra un mensaje con el nivel especificado.
  - **Parámetros**:
    - `level` (`ENUM`): Nivel del log.
    - `message` (`STRING`): Mensaje a registrar.

```cpp
Logger::log(Logger::LogLevel::WARNING, "Este es un mensaje de advertencia.");
```

- **`logCriticalEvent`**
  - **Descripción**: Registra un evento crítico tanto en el sistema de logging como en la auditoría.
  - **Parámetros**:
    - `message` (`STRING`): Mensaje del evento crítico.

```cpp
Logger::logCriticalEvent("Fallo crítico detectado en el servidor principal.");
```

- **`finalize`**
  - **Descripción**: Cierra el archivo de log y libera recursos.
  - **Parámetros**: Ninguno.

```cpp
Logger::finalize();
```

---

## Conclusión

Este documento proporciona una referencia integral de las funciones y librerías en MC++, diseñada para maximizar la eficiencia y escalabilidad en entornos críticos.
```
