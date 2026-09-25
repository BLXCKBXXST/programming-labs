# Работа с репозиторием в VS Code

В `programming/` лежат лабораторные по программированию, в `oop/` — работы по ООП.

## Подготовка

Установи [Git](https://git-scm.com/downloads), [VS Code](https://code.visualstudio.com/) и расширение C/C++ от Microsoft. Для сборки потребуются GCC/G++ или Clang; некоторые работы дополнительно используют CMake, SFML или CMocka (см. README конкретной лабораторной).

Настрой имя и адрес электронной почты для Git:

```bash
git config --global user.name "Имя"
git config --global user.email "адрес@example.com"
```

## Клонирование

В VS Code вызови `Git: Clone` через `Ctrl+Shift+P` или выполни:

```bash
git clone https://github.com/BLXCKBXXST/programming-labs.git
cd programming-labs
code .
```

Для отправки изменений войди в GitHub через VS Code или Git Credential Manager. Не сохраняй токены доступа в репозитории.

## Сохранение изменений

```bash
git status
git add programming/lab-01/
git commit -m "Update lab 01"
git push
```

Перед работой с другого компьютера выполняй `git pull`. В VS Code те же действия доступны через вкладку Source Control. Сборка и запуск описаны в README каждой лабораторной.
