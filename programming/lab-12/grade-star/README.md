# Звёздочка — callback-функция сравнения

## Что такое callback?

Callback (колбэк) — это когда мы **передаём функцию как аргумент** в другую функцию.

Вместо того чтобы писать отдельную `SortByPrice`, `SortBySize`, `SortByBrand`...  
Мы пишем **одну** `BubbleSortCallback`, которая не знает *как* сравнивать —  
она спрашивает об этом у переданной функции.

## Как это выглядит в коде

```c
// функция сортировки принимает третий аргумент — указатель на функцию сравнения
void BubbleSortCallback(Sneaker *arr, int n,
                        int (*cmp)(const Sneaker *, const Sneaker *));
```

Читаем `int (*cmp)(const Sneaker *, const Sneaker *)` как:  
«`cmp` — это указатель на функцию, которая принимает два кроссовка и возвращает int»

## Функции-компараторы

```c
// возвращает >0 если a дороже b — значит поставить b раньше
int CompareByPrice(const Sneaker *a, const Sneaker *b) {
    return a->price - b->price;
}

// возвращает >0 если размер a больше b
int CompareBySize(const Sneaker *a, const Sneaker *b) {
    return a->size - b->size;
}
```

## Как вызываем

```c
// сортируем по цене
BubbleSortCallback(arr, 10, CompareByPrice);

// сортируем по размеру — меняем только одно слово!
BubbleSortCallback(arr, 10, CompareBySize);
```

Это удобно: сортировка одна, а логика сравнения — снаружи.

## Сборка

```bash
gcc src/main.c src/sneakers.c -I include -o sneakers
./sneakers
```
