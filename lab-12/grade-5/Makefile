CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
AR      = ar
ARFLAGS = rcs

BUILD   = build
TARGET  = sneakers

.PHONY: all clean

all: $(BUILD) static shared $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/sneakers.o: src/sneakers.c include/sneakers.h
	$(CC) $(CFLAGS) -c $< -o $@

# статическая библиотека - встраивается в бинарник, внешний файл не нужен
static: $(BUILD)/sneakers.o
	$(AR) $(ARFLAGS) $(BUILD)/libsneakers.a $^

# динамическая библиотека - подгружается в память в рантайм, файл .so должен быть рядом
# -fPIC - позиционно-независимый код, без него .so не собрать
shared: src/sneakers.c include/sneakers.h
	$(CC) $(CFLAGS) -fPIC -shared $< -o $(BUILD)/libsneakers.so

$(TARGET): src/main.c $(BUILD)/libsneakers.a
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD) $(TARGET)
