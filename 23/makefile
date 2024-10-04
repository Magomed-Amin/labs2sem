# Makefile для сборки и запуска проекта

# Компилятор и флаги компиляции
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall

# Имена файлов
TARGET = client
OBJECTS = main.o tree.o lib.o

# Правило по умолчанию
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Правило сборки объектных файлов
main.o: main.c lib.h
	$(CC) $(CFLAGS) -c main.c

tree.o: tree.c lib.h
	$(CC) $(CFLAGS) -c tree.c

lib.o: lib.c lib.h
	$(CC) $(CFLAGS) -c lib.c

# Правило очистки
clean:
	rm -f $(OBJECTS) $(TARGET)

# Правило сборки и запуска
run: all
	./$(TARGET)
