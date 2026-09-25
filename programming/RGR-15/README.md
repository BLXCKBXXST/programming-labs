# РГР-15. Змейка

Консольная змейка на C++17, вариант 15. Есть три скорости, рекорды и настройки в `config.cfg`. Управление стрелками, пробел или P — пауза, R — заново, Esc — меню.

На Linux/macOS нужна ncurses:

```bash
g++ -std=c++17 -O2 snake.cpp -o snake -lncurses
./snake
```

На Windows (MinGW) собирается без неё: `g++ -std=c++17 -O2 snake.cpp -o snake.exe`. Там используются `conio.h` и `windows.h`.

Если хочется изменить размер поля или скорость, смотри `cols`, `rows`, `speed_easy`, `speed_medium` и `speed_hard` в конфиге. Рекорды сохраняются в `records.dat`.
