CC      = gcc
CFLAGS  = -Wall -Iinclude
AR      = ar
LIB     = libroom.a
OBJ     = src/room.o
BIN     = rooms

# цель all: полная сборка проекта
all: $(BIN)

# сборка статической библиотеки
$(LIB): $(OBJ)
	$(AR) rcs $@ $^

# компиляция исходных файлов в объектные
src/room.o: src/room.c include/room.h
	$(CC) $(CFLAGS) -c $< -o $@

# линковка исполняемого файла
$(BIN): src/main.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

# цель clean: удаление всех скомпилированных файлов
clean:
	rm -f $(OBJ) $(LIB) $(BIN)

.PHONY: all clean
