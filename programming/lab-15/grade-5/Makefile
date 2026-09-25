CC     = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = program
SRCS   = main.c record.c menu.c

$(TARGET): $(SRCS) record.h menu.h
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) database.dat database.rle database_restored.dat
