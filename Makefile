# Makefile para compilar y gestionar el proyecto MC++

# Definir compilador y banderas de compilación
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
INCLUDES := -I./include

# Definir directorios de fuente y destino
SRCDIR := src
BUILDDIR := build
TARGET := bin/mc++

# Recopilar todos los archivos fuente
SRCS := $(wildcard $(SRCDIR)/**/*.cpp $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Reglas para construir el proyecto completo
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Regla para compilar cada archivo fuente en su archivo objeto correspondiente
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Limpieza de archivos objeto y binarios
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Instalación (opcional) del ejecutable
install: $(TARGET)
	@echo "Instalando MC++ en /usr/local/bin"
	cp $(TARGET) /usr/local/bin/mc++

# Desinstalación
uninstall:
	@echo "Eliminando MC++ de /usr/local/bin"
	rm -f /usr/local/bin/mc++

# Ejecutar pruebas
test: $(TARGET)
	@echo "Ejecutando pruebas"
	@./tests/run_tests.sh

# Documentación
docs:
	@echo "Generando documentación"
	@doxygen Doxyfile

.PHONY: all clean install uninstall test docs
