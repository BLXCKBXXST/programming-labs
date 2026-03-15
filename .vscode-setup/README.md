# 💻 Как подключить этот репозиторий в VS Code и работать с ним

Это подробная инструкция — даже если ты никогда не работал с Git или GitHub, ты справишься.

---

## 📦 Часть 1: Установка нужных программ

### 1.1 Установи VS Code

1. Перейди на сайт: https://code.visualstudio.com
2. Нажми **Download** и установи как обычную программу.

### 1.2 Установи Git

> Git — это программа для сохранения и отправки твоего кода на GitHub.

**Windows:**
1. Перейди на: https://git-scm.com/download/win
2. Скачай и установи (все галочки по умолчанию, просто дальше-дальше).

**macOS:**
```bash
brew install git
```
если нет Homebrew: https://brew.sh

**Linux (Ubuntu/Debian):**
```bash
sudo apt update && sudo apt install git
```

**Проверка** (открой терминал или PowerShell):
```bash
git --version
# должно написать: git version 2.x.x
```

---

## ⚙️ Часть 2: Настройка Git (один раз навсегда)

Открой терминал (в Windows: нажми `Win+R`, напиши `cmd`, Enter) и введи:

```bash
git config --global user.name "Твоё Имя"
git config --global user.email "твой@email.com"
```

> Обязательно используй тот же email, что у тебя на GitHub!

---

## 🔑 Часть 3: Авторизация в GitHub (чтобы можно было отправлять код)

### Способ 1: через VS Code (проще всего)

1. Открой VS Code.
2. Слева найди иконку флажка/веточки (**Source Control**, или `Ctrl+Shift+G`).
3. Нажми **Clone Repository**.
4. VS Code спросит залогиниться в GitHub — нажми **Allow** и войди в свой аккаунт.
5. Дальше см. Часть 4.

### Способ 2: через Personal Access Token (PAT)

Если VS Code не спрашивает GitHub-автаризацию автоматически:

1. Открой https://github.com и войди в свой аккаунт.
2. Нажми на свою аватарку (справа вверху) → **Settings**.
3. Слева внизу найди **Developer settings** → **Personal access tokens** → **Tokens (classic)**.
4. Нажми **Generate new token (classic)**.
5. В поле **Note** напиши например `vscode`.
6. Поставь галочку напротив `repo` (полный доступ к репозиториям).
7. Нажми **Generate token** внизу.
8. Скопируй токен (он показывается только один раз!).

При первом `git push` Git спросит пароль — вставь вместо пароля скопированный токен.

---

## 📂 Часть 4: Клонирование репозитория на свой компьютер

> Клонировать — значит скачать копию репозитория к себе на компьютер.

### Через VS Code (проще)

1. Открой VS Code.
2. Нажми `Ctrl+Shift+P` (или `Cmd+Shift+P` на Mac).
3. Напиши: `Git: Clone` и нажми Enter.
4. Вставь ссылку:
   ```
   https://github.com/BLXCKBXXST/lab-works.git
   ```
5. Выбери папку, куда сохранить (например `C:\Users\ТвоёИмя\Documents`).
6. Нажми **Open** — проект откроется в VS Code.

### Через терминал

```bash
# перейди в папку, где хочешь хранить проект
# Windows:
cd C:\Users\YourName\Documents

# macOS/Linux:
cd ~/Documents

# клонировать
git clone https://github.com/BLXCKBXXST/lab-works.git

# открыть папку в VS Code
code lab-works
```

---

## ✏️ Часть 5: Изменение кода и отправка на GitHub

Это самая важная часть. Цикл выглядит так:

```
Редактируешь файлы  →  git add  →  git commit  →  git push  →  GitHub
```

### Через VS Code (кнопками, без команд)

1. Измени любой файл.
2. Нажми на иконку **Source Control** слева (`Ctrl+Shift+G`).
3. Ты увидишь список изменённых файлов.
4. Нажми **+** рядом с файлом (или **Stage All Changes** — значок `+` рядом с заголовком Changes).
5. В поле сверху (где написано «Message») напиши описание, например: `Add lab-12 grade-3`.
6. Нажми кнопку **✓ Commit**.
7. Нажми **Sync Changes** (или стрелочку вверх-вниз `↑↓`) — это отправит код на GitHub.

### Через терминал (3 команды)

```bash
# 1. Добавить все изменения в очередь
git add .

# 2. Сделать коммит с описанием
git commit -m "Напиши что сделал"

# 3. Отправить на GitHub
git push
```

---

## 🔄 Часть 6: Получить последние изменения с GitHub

Если кто-то ещё или ты сам с другого устройства изменил файлы на GitHub:

```bash
git pull
```

Или в VS Code: нажми кнопку **Sync Changes** (`↑↓`).

---

## 🛠️ Часть 7: Полезные расширения VS Code для работы с C

Установи их через `Ctrl+Shift+X` (Extensions):

| Расширение | Для чего |
|---|---|
| **C/C++** (Microsoft) | подсветка синтаксиса, автодополнение кода |
| **GitLens** | показывает кто и когда изменил каждую строку |
| **GitHub Pull Requests** | работа с PR прямо в редакторе |
| **Error Lens** | показывает ошибки прямо в строке кода |

---

## ⚠️ Частые проблемы и решения

### «Плохой автор» при push

```bash
git config --global user.email "твой@email.com"
git config --global user.name "YourName"
```

### «Permission denied» / «401 Unauthorized»

Zначит нет авторизации. Создай новый PAT (часть 3, способ 2).

### «git push» просит username/password

Сохрани токен, чтобы не вводить каждый раз:

```bash
git config --global credential.helper store
```

После первого `git push` введи логин и токен вместо пароля — дальше хранится автоматически.

### «failed to push: tip of your current branch is behind»

Сначала скачай последние изменения, потом отправь:

```bash
git pull
git push
```

---

## 📚 Шпаргалка: самые нужные Git-команды

```bash
git status          # посмотреть что изменилось
git log --oneline   # история коммитов
git diff            # смотреть все изменения в деталях
git add .           # добавить все изменения в очередь
git commit -m "..." # сохранить снимок изменений
git push            # отправить на GitHub
git pull            # скачать последние изменения с GitHub
```
