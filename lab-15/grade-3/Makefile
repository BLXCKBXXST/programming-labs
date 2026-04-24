CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = program
TARGET2 = program_syscall

all: $(TARGET) $(TARGET2)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

$(TARGET2): main_syscall.c
	$(CC) $(CFLAGS) main_syscall.c -o $(TARGET2)

clean:
	rm -f $(TARGET) $(TARGET2)
