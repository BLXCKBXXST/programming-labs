CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
AR      = ar
ARFLAGS = rcs

BUILD   = build
LIB     = $(BUILD)/libsneakers.a
TARGET  = sneakers

.PHONY: all clean

all: $(BUILD) $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

# компилируем sneakers.c в объектный файл
$(BUILD)/sneakers.o: src/sneakers.c include/sneakers.h
	$(CC) $(CFLAGS) -c $< -o $@

# собираем статическую библиотеку .a из объектного файла
# ar - архиватор, rcs - создаёт/заменяет файлы в архиве
$(LIB): $(BUILD)/sneakers.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILD)/main.o: src/main.c include/sneakers.h
	$(CC) $(CFLAGS) -c $< -o $@

# линкуем main.o со статической библиотекой
$(TARGET): $(BUILD)/main.o $(LIB)
	$(CC) $^ -o $@

clean:
	rm -rf $(BUILD) $(TARGET)
