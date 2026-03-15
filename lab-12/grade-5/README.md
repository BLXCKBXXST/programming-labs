# Lab 12 — Grade 5

Добавлено измерение времени через `gettimeofday()` и динамическая библиотека `.so`.

## Сборка вручную
```bash
# 1. компилируем с -fPIC (обязательно для .so)
gcc -Wall -Iinclude -fPIC -c src/sneakers.c -o sneakers.o

# 2. статическая библиотека
ar rcs libsneakers.a sneakers.o

# 3. динамическая библиотека
gcc -Wall -Iinclude -fPIC -shared src/sneakers.c -o libsneakers.so

# 4. линкуем со статической
gcc -Wall -Iinclude src/main.c libsneakers.a -o sneakers

# 5. запускаем
./sneakers
```

## Разница между статической и динамической библиотекой

| | Статическая `.a` | Динамическая `.so` |
|---|---|---|
| Когда подключается | При линковке (compile time) | При запуске (runtime) |
| Файл .so рядом | Не нужен | Обязателен |
| Размер бинарника | Больше | Меньше |
| Обновление библиотеки | Нужно пересобрать | Достаточно заменить .so файл |
