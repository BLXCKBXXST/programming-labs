# Динамическая библиотека и время сортировки

Теперь размер массива не фиксирован, данные выделяются через `malloc`. Сравниваем время сортировки для 100, 10 000 и 100 000 элементов. На большом массиве пузырёк заметно тормозит — у него квадратичная сложность.

Обычная сборка: `gcc src/main.c src/sneakers.c -I include -o sneakers`.

Для `.so` из этой папки:

```bash
gcc -fPIC -c src/sneakers.c -I include -o sneakers.o
gcc -shared sneakers.o -o libsneakers.so
gcc src/main.c -I include -L . -lsneakers -o sneakers
LD_LIBRARY_PATH=. ./sneakers
```

Разницу по времени смотрим в выводе программы, а не считаем заранее: она зависит от машины.
