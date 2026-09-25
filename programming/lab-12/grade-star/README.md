# Сортировка с callback

Дополнительное задание: одна сортировка, но разные способы сравнения. Вместо нескольких почти одинаковых функций передаём в `BubbleSortCallback` указатель на функцию сравнения — по цене, размеру или бренду.

[Код](src/sneakers.c) и [пример вызова](src/main.c).

`gcc src/main.c src/sneakers.c -I include -o sneakers && ./sneakers`
