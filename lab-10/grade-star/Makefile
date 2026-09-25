# Звёздочка к лабе 10. Makefile, который компилирует исходники
# в объектные файлы (.o), а потом линкует их в один бинарник.
#
# Берём за основу код grade-4: main.c + fraction.c + fraction.h.
# Цели:
#   all       — собрать программу из объектников
#   clean     — удалить .o и бинарник
#   <file>.o  — отдельная цель для каждого объектника
#
# Полезные spell'ы:
#   $@   — имя цели
#   $<   — первая зависимость
#   $^   — все зависимости

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
SRCS    := ../grade-4/main.c ../grade-4/fraction.c
OBJS    := main.o fraction.o
TARGET  := fraction

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

main.o:     ../grade-4/main.c     ../grade-4/fraction.h
	$(CC) $(CFLAGS) -c $< -o $@

fraction.o: ../grade-4/fraction.c ../grade-4/fraction.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
