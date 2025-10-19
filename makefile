# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c99

# Nombre del ejecutable
TARGET = lru

# Archivos fuente
SOURCES = main.c cache.c

# Archivos objeto
OBJECTS = main.o cache.o

# Archivos header
HEADERS = cache.h

# Regla por defecto
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compilar archivos objeto
main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

cache.o: cache.c $(HEADERS)
	$(CC) $(CFLAGS) -c cache.c

# Limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Limpiar y recompilar
rebuild: clean all

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
