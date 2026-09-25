.PHONY: all clean grade-3 grade-4 grade-5 grade-star

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

all: grade-3 grade-4 grade-5 grade-star

# grade-3 — один файл
grade-3: grade-3/sneakers
grade-3/sneakers: grade-3/main.c
	$(CC) $(CFLAGS) $< -o $@

# grade-4 — раздельные main.c и sneakers.c, заголовок в include/
grade-4: grade-4/sneakers
grade-4/sneakers: grade-4/src/main.c grade-4/src/sneakers.c grade-4/include/sneakers.h
	$(CC) $(CFLAGS) -Igrade-4/include grade-4/src/main.c grade-4/src/sneakers.c -o $@

# grade-5 — то же + замер времени (-O2)
grade-5: grade-5/sneakers
grade-5/sneakers: grade-5/src/main.c grade-5/src/sneakers.c grade-5/include/sneakers.h
	$(CC) $(CFLAGS) -O2 -Igrade-5/include grade-5/src/main.c grade-5/src/sneakers.c -o $@

# grade-star — callback в сортировке
grade-star: grade-star/sneakers
grade-star/sneakers: grade-star/src/main.c grade-star/src/sneakers.c grade-star/include/sneakers.h
	$(CC) $(CFLAGS) -Igrade-star/include grade-star/src/main.c grade-star/src/sneakers.c -o $@

clean:
	rm -f grade-3/sneakers grade-4/sneakers grade-5/sneakers grade-star/sneakers
