### **Parte 1: Requisitos Previos y Clonación del Repositorio**

```markdown
# Guía de Instalación de MC++

Esta guía proporciona instrucciones detalladas para instalar MC++ en diversos sistemas operativos. MC++ está diseñado para sistemas de alto rendimiento, por lo que es crucial que sigas estas instrucciones cuidadosamente para garantizar un funcionamiento óptimo.

---

## Tabla de Contenidos

1. [Requisitos Previos](#requisitos-previos)
2. [Clonar el Repositorio](#clonar-el-repositorio)
3. [Configuración de Dependencias](#configuración-de-dependencias)
4. [Compilación del Proyecto](#compilación-del-proyecto)
5. [Configuración de Variables de Entorno](#configuración-de-variables-de-entorno)
6. [Ejecución de Pruebas](#ejecución-de-pruebas)
7. [Solución de Problemas Comunes](#solución-de-problemas-comunes)
8. [Desinstalación](#desinstalación)

---

## 1. Requisitos Previos

### Sistemas Operativos Compatibles
MC++ es compatible con los siguientes sistemas:
- **Linux**: Preferiblemente distribuciones basadas en Ubuntu o Debian. Otras distribuciones pueden requerir ajustes adicionales.
- **Windows**: Requiere Windows 10 o superior, con soporte para herramientas de desarrollo como Visual Studio.
- **macOS**: Compatible con versiones 11.0 (Big Sur) o posteriores.

### Herramientas de Compilación Requeridas
- **Linux/macOS**:
  - GCC 10.0+ o Clang 11.0+.
  - CMake 3.18+ para configuraciones multiplataforma.
- **Windows**:
  - Microsoft Visual Studio 2019 (o superior) con soporte completo de C++.
  - Opcional: PowerShell o Git Bash para facilitar comandos.

### Dependencias Adicionales
Asegúrate de instalar las siguientes librerías y herramientas:
- **Python 3.8+**: Para interoperabilidad con Python y scripts auxiliares.
- **Boost 1.75+**: Librería clave para manejo avanzado de hilos y sincronización.
- **JSON for Modern C++ (nlohmann/json)**: Necesario para leer y escribir configuraciones en formato JSON.
- **OpenSSL 1.1+**: Utilizado para funciones de cifrado y seguridad en MC++.

---

## 2. Clonar el Repositorio

Sigue los pasos a continuación para obtener el código fuente:

### Clonar con Git
1. Abre tu terminal o línea de comandos.
2. Ejecuta el siguiente comando:
   ```bash
   git clone https://github.com/tuusuario/MCpp.git
   cd MCpp
   ```
   Esto descargará el código fuente en un directorio llamado `MCpp`.

### Verificar la Integridad del Repositorio
Es importante verificar que se ha descargado correctamente:
- Comprueba la existencia de carpetas clave como `src`, `include`, y `docs`.
- Asegúrate de que el archivo `README.md` esté presente en el directorio raíz.

### Actualizar el Repositorio (Opcional)
Si ya tienes una copia antigua del repositorio, asegúrate de actualizarla:
```bash
git pull origin main
```


---

## 3. Configuración de Dependencias

Para que MC++ funcione correctamente, necesitas instalar varias dependencias esenciales. A continuación, te guiamos por los pasos necesarios para Linux, macOS y Windows.

---

### **Instalación de Dependencias en Linux**

#### CMake
CMake es una herramienta fundamental para compilar MC++. Instálalo ejecutando:
```bash
sudo apt-get update
sudo apt-get install cmake
```

#### Boost
Boost proporciona herramientas avanzadas para manejo de hilos y sincronización. Instálalo ejecutando:
```bash
sudo apt-get install libboost-all-dev
```

#### OpenSSL
Instala OpenSSL para funciones de cifrado y seguridad:
```bash
sudo apt-get install libssl-dev
```

#### JSON para Modern C++
Descarga la biblioteca oficial desde su repositorio:
```bash
git clone https://github.com/nlohmann/json.git
cd json
mkdir build && cd build
cmake ..
make
sudo make install
```

#### Python 3
Asegúrate de que Python 3.8 o superior esté instalado:
```bash
sudo apt-get install python3 python3-pip
```

---

### **Instalación de Dependencias en macOS**

#### CMake
Si tienes instalado Homebrew, usa este comando:
```bash
brew install cmake
```

#### Boost
Instala Boost con Homebrew:
```bash
brew install boost
```

#### OpenSSL
Instala OpenSSL para cifrado seguro:
```bash
brew install openssl
```

#### JSON para Modern C++
Clona e instala la biblioteca:
```bash
git clone https://github.com/nlohmann/json.git
cd json
mkdir build && cd build
cmake ..
make
sudo make install
```

#### Python 3
Instala la versión más reciente de Python 3:
```bash
brew install python
```

---

### **Instalación de Dependencias en Windows**

#### CMake
Descarga el instalador desde [cmake.org](https://cmake.org) y sigue las instrucciones. Asegúrate de agregar CMake al `PATH` durante la instalación.

#### Boost
1. Descarga el paquete oficial desde [Boost.org](https://www.boost.org).
2. Extrae el archivo y compila las bibliotecas con:
   ```powershell
   bootstrap.bat
   b2 install
   ```

#### OpenSSL
Descarga el instalador de OpenSSL desde [OpenSSL.org](https://www.openssl.org) y sigue las instrucciones.

#### JSON para Modern C++
1. Descarga el código desde [GitHub](https://github.com/nlohmann/json).
2. Usa CMake para compilar y agregar la biblioteca al proyecto.

#### Python 3
Descarga el instalador desde [Python.org](https://www.python.org) y asegúrate de seleccionar la opción "Add Python to PATH" durante la instalación.

---

### **Verificación de Dependencias**

Después de instalar todas las dependencias, verifica que están correctamente configuradas ejecutando:
```bash
cmake --version
g++ --version
python3 --version
```
También verifica que las librerías están disponibles en las rutas esperadas (e.g., `/usr/lib` en Linux).

---

## 4. Compilación del Proyecto

Después de configurar las dependencias, el siguiente paso es compilar MC++. Este proceso varía ligeramente según el sistema operativo. Sigue los pasos específicos para tu plataforma.

---

### **Compilación en Linux**

1. **Crea un Directorio para la Compilación:**
   Para mantener organizado el proyecto, crea un directorio `build` dentro del repositorio.
   ```bash
   mkdir build && cd build
   ```

2. **Configura el Proyecto con CMake:**
   Configura el entorno de compilación:
   ```bash
   cmake ..
   ```

3. **Compila el Proyecto:**
   Ejecuta el comando `make` para construir MC++:
   ```bash
   make
   ```

4. **Verifica los Binarios:**
   Los binarios se generarán en el directorio `build/bin`. Verifica su existencia:
   ```bash
   ls bin/
   ```

---

### **Compilación en macOS**

1. **Crea un Directorio para la Compilación:**
   Dentro del directorio del repositorio:
   ```bash
   mkdir build && cd build
   ```

2. **Configura el Proyecto con CMake:**
   Configura el entorno de compilación:
   ```bash
   cmake -DCMAKE_BUILD_TYPE=Release ..
   ```

3. **Compila el Proyecto:**
   Utiliza el comando `make` para compilar:
   ```bash
   make
   ```

4. **Valida los Binarios:**
   Los binarios estarán en `build/bin`. Verifica que se hayan creado correctamente:
   ```bash
   ls bin/
   ```

---

### **Compilación en Windows**

1. **Configura el Proyecto con CMake:**
   Abre PowerShell y navega al directorio del repositorio:
   ```powershell
   mkdir build
   cd build
   cmake .. -G "Visual Studio 16 2019"
   ```

2. **Compila con Visual Studio:**
   Abre el archivo `MCpp.sln` generado en Visual Studio. Asegúrate de seleccionar el modo "Release" antes de compilar.

3. **Verifica los Binarios:**
   Los binarios se generarán en `build\bin`. Usa el explorador de archivos o ejecuta:
   ```powershell
   dir bin
   ```

---

### **Configuraciones Adicionales**

#### Configuración de Opciones de CMake
Puedes personalizar la compilación utilizando opciones avanzadas de CMake:

- **Activar Compilación Paralela (Linux/macOS):**
  ```bash
  cmake -DCMAKE_BUILD_TYPE=Release ..
  make -j$(nproc)
  ```

- **Especificar Ruta de Dependencias (Linux/macOS):**
  ```bash
  cmake -DBOOST_ROOT=/ruta/a/boost -DOPENSSL_ROOT_DIR=/ruta/a/openssl ..
  ```

#### Limpieza de Archivos de Compilación
Si necesitas recompilar desde cero, elimina el directorio `build`:
```bash
rm -rf build
```
En Windows:
```powershell
rd /s /q build
```

---

## 5. Configuración de Variables de Entorno

Para que MC++ funcione correctamente, es necesario configurar varias variables de entorno. Estas variables aseguran que el compilador, los binarios y las configuraciones estén accesibles para el sistema operativo.

---

### **Configuración en Linux y macOS**

1. **Definir Variables de Entorno:**
   Agrega las siguientes líneas al archivo de inicialización de tu terminal (`.bashrc`, `.zshrc`, etc.):
   ```bash
   export MC_HOME=/ruta/a/MCpp
   export PATH=$MC_HOME/bin:$PATH
   export MC_CONFIG_PATH=$MC_HOME/configs
   ```

2. **Aplicar los Cambios:**
   Ejecuta el siguiente comando para cargar los cambios:
   ```bash
   source ~/.bashrc
   ```

3. **Validar Configuración:**
   Verifica que las variables estén configuradas correctamente:
   ```bash
   echo $MC_HOME
   echo $PATH
   ```

---

### **Configuración en Windows**

1. **Abrir Configuración de Variables de Entorno:**
   - Ve al Panel de Control.
   - Busca "Variables de Entorno" en la barra de búsqueda.
   - Haz clic en "Editar las variables de entorno del sistema".

2. **Crear Nuevas Variables:**
   Agrega las siguientes variables:
   - `MC_HOME` con el valor `C:\ruta\a\MCpp`.
   - `MC_CONFIG_PATH` con el valor `%MC_HOME%\configs`.

3. **Editar la Variable `PATH`:**
   Agrega `%MC_HOME%\bin` al final de la lista de rutas en la variable `PATH`.

4. **Validar Configuración:**
   Abre una nueva ventana de PowerShell y ejecuta:
   ```powershell
   echo $env:MC_HOME
   echo $env:PATH
   ```

---

### **Configuraciones Opcionales**

#### Establecer un Alias para Comandos Frecuentes (Linux/macOS)
Para facilitar el uso de comandos, puedes configurar alias:
```bash
alias mc++run="$MC_HOME/bin/mc++"
alias mc++test="$MC_HOME/bin/mc++_test"
```
Agrega estos alias al archivo de inicialización de tu terminal (`.bashrc`, `.zshrc`, etc.).

#### Configuración Personalizada en `mc++.json`
El archivo `mc++.json` puede usarse para configurar parámetros específicos. Ejemplo:
```json
{
    "default_log_level": "INFO",
    "performance_mode": "balanced",
    "max_thread_count": 8
}
```
Coloca este archivo en la ruta especificada por `MC_CONFIG_PATH`.

---

### **Siguientes Pasos**

Una vez configuradas las variables de entorno, puedes proceder a ejecutar pruebas para validar la instalación. Continúa con la **Parte 5** para realizar la validación y resolver posibles errores.

---

## 6. Ejecución de Pruebas

Después de completar la instalación y configurar las variables de entorno, es fundamental validar que MC++ funcione correctamente. Para ello, utiliza las pruebas incluidas en el proyecto.

---

### **Ejecución de Pruebas Unitarias**

1. **Navegar al Directorio de Pruebas:**
   Dirígete al directorio `tests` dentro de la carpeta de compilación:
   ```bash
   cd build/tests
   ```

2. **Ejecutar Todas las Pruebas:**
   Usa el ejecutable `run_all_tests` generado durante la compilación:
   ```bash
   ./run_all_tests
   ```
   Esto ejecutará todas las pruebas unitarias y mostrará un resumen con los resultados.

3. **Verificar los Resultados:**
   - Una salida de `PASSED` indica que las pruebas se ejecutaron correctamente.
   - En caso de errores, revisa los logs generados para identificar problemas específicos.

---

### **Ejecución de Pruebas de Rendimiento**

1. **Ejecutar Pruebas de Carga:**
   Usa los scripts de pruebas de carga en `performance_tests`:
   ```bash
   ./run_performance_tests
   ```

2. **Analizar el Rendimiento:**
   Los resultados incluirán métricas como:
   - Tiempo de ejecución.
   - Uso de CPU y memoria.
   - Análisis de cuellos de botella.

3. **Configurar Parámetros para Mejorar Rendimiento:**
   Ajusta las configuraciones en `mc++.json` según los resultados de las pruebas. Por ejemplo:
   ```json
   {
       "performance_mode": "high_performance",
       "max_thread_count": 16
   }
   ```

---

### **Pruebas de Integración**

1. **Verificar Integración de Librerías:**
   Ejecuta pruebas específicas para validar la integración entre módulos:
   ```bash
   ./integration_tests
   ```

2. **Evaluar Dependencias Externas:**
   Revisa que las librerías externas (e.g., Boost, OpenSSL) estén funcionando correctamente.

---

### **Revisión de Logs de Pruebas**

Los logs generados durante las pruebas se almacenan en el directorio `logs`:
- **`unit_test.log`**: Detalles de pruebas unitarias.
- **`performance_test.log`**: Resultados de pruebas de carga.
- **`integration_test.log`**: Información sobre pruebas de integración.

Utiliza un visor de logs para analizar los resultados:
```bash
cat logs/unit_test.log
```

---

### **Pasos Adicionales**

Si las pruebas fallan:
1. Revisa la configuración de variables de entorno:
   ```bash
   echo $MC_HOME
   echo $MC_CONFIG_PATH
   ```

2. Verifica las versiones de dependencias:
   ```bash
   cmake --version
   gcc --version
   openssl version
   ```

3. Consulta la sección **Solución de Problemas Comunes** en este documento.

---

Continúa con la **Parte 6** para explorar problemas comunes y cómo solucionarlos.
```

---

### **Parte 6: Solución de Problemas Comunes**

```markdown
---

## 7. Solución de Problemas Comunes

A continuación, se presentan soluciones para los problemas más frecuentes que pueden surgir durante la instalación o configuración de MC++.

---

### **Problemas de Dependencias Faltantes**

#### **Mensaje de Error: "CMake no encontrado"**
- **Causa:** CMake no está instalado o no está en el PATH.
- **Solución:**
  1. Instala CMake siguiendo las instrucciones de la sección [Configuración de Dependencias](#configuración-de-dependencias).
  2. Verifica que CMake esté en el PATH:
     ```bash
     cmake --version
     ```

#### **Mensaje de Error: "No se encontró Boost"**
- **Causa:** Boost no está instalado o no se configuró correctamente.
- **Solución:**
  - Instala Boost usando el gestor de paquetes correspondiente.
  - Asegúrate de que la ruta de Boost sea detectada por CMake. Puedes especificar manualmente la ruta:
    ```bash
    cmake -DBOOST_ROOT=/ruta/a/boost ..
    ```

---

### **Errores de Compilación**

#### **Mensaje de Error: "Compilador incompatible"**
- **Causa:** La versión del compilador no es compatible.
- **Solución:**
  - Verifica la versión de GCC o Clang:
    ```bash
    gcc --version
    clang --version
    ```
  - Actualiza a la versión requerida:
    - **Ubuntu/Debian**:
      ```bash
      sudo apt-get install gcc-10
      ```

#### **Error: "No se encontró el archivo de encabezado"**
- **Causa:** Archivos de encabezado faltantes en la carpeta `include`.
- **Solución:**
  1. Asegúrate de que todos los archivos estén presentes en el repositorio.
  2. Limpia y recompila el proyecto:
     ```bash
     rm -rf build
     mkdir build
     cd build
     cmake ..
     make
     ```

---

### **Errores en las Pruebas**

#### **Mensaje de Error: "Fallo en prueba unitaria"**
- **Causa:** Problemas con el código o configuraciones incorrectas.
- **Solución:**
  - Revisa los logs de prueba:
    ```bash
    cat logs/unit_test.log
    ```
  - Verifica que las configuraciones sean correctas en `mc++.json`.

#### **Mensaje de Error: "Fallo en la prueba de integración"**
- **Causa:** Problemas en la interacción entre módulos.
- **Solución:**
  - Asegúrate de que las dependencias externas estén configuradas correctamente.
  - Ejecuta pruebas individuales de cada módulo para identificar el problema.

---

### **Otros Problemas**

#### **Mensaje de Error: "Variable de entorno no configurada"**
- **Causa:** Las variables de entorno no se han establecido correctamente.
- **Solución:**
  - Configura las variables según las instrucciones de la sección [Configuración de Variables de Entorno](#configuración-de-variables-de-entorno).

#### **MC++ no se ejecuta correctamente en Windows**
- **Causa:** Problemas con permisos o rutas.
- **Solución:**
  - Ejecuta PowerShell como administrador.
  - Verifica las rutas y permisos de los archivos:
    ```powershell
    Get-ChildItem -Path "C:\ruta\a\MCpp"
    ```

---

Continúa con la **Parte 7** para desinstalar MC++ si es necesario.
```

---

### **Parte 7: Desinstalación**

```markdown
---

## 8. Desinstalación

Si deseas eliminar MC++ de tu sistema, sigue las instrucciones específicas para tu plataforma.

---

### **Linux/macOS**

1. **Eliminar el Directorio del Proyecto:**
   ```bash
   rm -rf /ruta/a/MCpp
   ```

2. **Eliminar Variables de Entorno:**
   - Abre el archivo de configuración de tu terminal (`.bashrc`, `.zshrc`, etc.) y elimina las líneas relacionadas con MC++:
     ```bash
     export MC_HOME=/ruta/a/MCpp
     export MC_CONFIG_PATH=$MC_HOME/configs
     ```
   - Aplica los cambios:
     ```bash
     source ~/.bashrc
     ```

---

### **Windows**

1. **Eliminar Archivos y Directorios:**
   - Abre PowerShell como administrador y ejecuta:
     ```powershell
     rd /s /q C:\ruta\a\MCpp
     ```

2. **Eliminar Variables de Entorno:**
   - Ve a "Variables de Entorno" en la configuración del sistema.
   - Elimina `MC_HOME` y `MC_CONFIG_PATH` de la lista de variables.

---

### **Limpieza Adicional**

Si se instalaron dependencias específicas para MC++:
- Elimina Boost y OpenSSL si ya no los necesitas.
- Limpia los paquetes instalados mediante tu gestor de paquetes (`apt`, `brew`, etc.).

---

Con esto, MC++ será completamente desinstalado de tu sistema. Si deseas volver a instalarlo, consulta esta guía desde el inicio.
```
