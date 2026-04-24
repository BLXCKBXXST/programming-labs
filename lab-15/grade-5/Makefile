CC     = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = program
SRCS   = main.c employee.c menu.c

$(TARGET): $(SRCS) employee.h menu.h
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) database.dat database.rle database_restored.dat
