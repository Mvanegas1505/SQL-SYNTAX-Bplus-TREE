# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Archivos fuente
SRCS = main.cpp ArbolBPlus.cpp AnalizadorSQL.cpp Dato.cpp

# Archivos de encabezado
HEADERS = ArbolBPlus.h AnalizadorSQL.h BpNode.h Dato.h

# Nombre del ejecutable
TARGET = sql_cli

# Regla principal: compila el proyecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar archivos de compilación
clean:
	rm -f $(TARGET) *.o
