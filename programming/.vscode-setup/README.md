# Как работать с репозиторием

Для редактирования удобнее всего VS Code с расширением C/C++ и установленным Git. Большинство старых лабораторных собирается через GCC, позже встречаются CMake и дополнительные библиотеки — они указаны возле самих заданий.

Если репозиторий ещё не скачан:

```bash
git clone https://github.com/BLXCKBXXST/programming-labs.git
cd programming-labs
code .
```

Лабы по программированию лежат в `programming/`, по ООП — в `oop/`. Чтобы отправлять коммиты, войди в GitHub через VS Code или Git Credential Manager и один раз укажи `git config --global user.name` и `user.email`.

Обычный цикл: `git pull` перед работой, затем `git add`, `git commit` и `git push`. Токены доступа в репозитории не хранить.
