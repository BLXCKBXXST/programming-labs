CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -I.
AR      = ar
ARFLAGS = rcs

# Статическая библиотека
LIB     = libcipher.a
LIB_SRC = cipher.c
LIB_OBJ = cipher.o

# Исполняемый файл
TARGET  = polibi
MAIN_OBJ = main.o

.PHONY: all clean

all: $(TARGET)

# Собираем статическую библиотеку
$(LIB): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(LIB_OBJ): $(LIB_SRC) cipher.h
	$(CC) $(CFLAGS) -c $< -o $@

# Собираем объектник main
$(MAIN_OBJ): main.c cipher.h
	$(CC) $(CFLAGS) -c $< -o $@

# Линкуем исполняемый файл со статической библиотекой
$(TARGET): $(MAIN_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) -L. -lcipher

clean:
	rm -f $(TARGET) $(LIB) *.o
