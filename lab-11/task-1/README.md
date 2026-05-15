# Задача 1 — Segmentation fault

## Симптом

```
$ gcc before.c -o before && ./before
Ошибка сегментирования (сделан дамп памяти)
```

## Почему падает

[before.c](before.c):

```c
void init(int *arr, int n) {
    arr = malloc(n * sizeof(int));   // ← присваиваем КОПИИ
    ...
}

int main() {
    int *arr = NULL;
    init(arr, n);                    // ← arr в main остаётся NULL
    printf("%d\n", arr[i]);          // ← разыменование NULL → SIGSEGV
}
```

Параметр `int *arr` в функции — это **локальная копия** указателя. `malloc` записывает адрес выделенной памяти в копию. Оригинальная `arr` в `main` так и остаётся `NULL`. При попытке прочитать `arr[i]` процесс получает `SIGSEGV`.

> Это классическая ошибка «передача по значению, ожидая передачу по ссылке».

## Фикс

[after.c](after.c) — функция **возвращает** указатель:

```c
int *init(int n) {
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = i;
    return arr;
}

int main(void) {
    int *arr = init(10);
    ...
    free(arr);
}
```

Альтернативный вариант (для продвинутых) — передавать `int **`, чтобы записать в саму переменную из `main`. Но возврат значения проще читается.

## Проверка

```bash
gcc after.c -o after && ./after
# выводит 0 1 2 3 ... 9
```
