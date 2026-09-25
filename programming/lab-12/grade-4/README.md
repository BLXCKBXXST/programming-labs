# Статическая библиотека

Ту же сортировку разнесли по файлам: [заголовок](include/sneakers.h), [функции](src/sneakers.c), [main](src/main.c). Из функций собирается `libsneakers.a`.

Если собирать вручную из этой папки:

```bash
gcc -c src/sneakers.c -I include -o sneakers.o
ar rcs libsneakers.a sneakers.o
gcc src/main.c -I include -L . -lsneakers -o sneakers
./sneakers
```

Без библиотеки тоже можно: `gcc src/main.c src/sneakers.c -I include -o sneakers`. Но цель этой части как раз потренироваться со статической сборкой.
