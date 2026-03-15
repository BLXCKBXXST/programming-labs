CC     = gcc
CFLAGS = -Wall -Iinclude
AR     = ar
LIB    = libsneakers.a
OBJ    = src/sneakers.o
BIN    = sneakers

# цель all: полная сборка проекта
all: $(BIN)

# сборка статической библиотеки
$(LIB): $(OBJ)
	$(AR) rcs $@ $^

# компиляция исходных файлов в объектные
src/sneakers.o: src/sneakers.c include/sneakers.h
	$(CC) $(CFLAGS) -c $< -o $@

# линковка исполняемого файла
$(BIN): src/main.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

# цель clean: удаление всех скомпилированных файлов
clean:
	rm -f $(OBJ) $(LIB) $(BIN)

.PHONY: all clean
