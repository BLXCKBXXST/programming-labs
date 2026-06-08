#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>

#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
  #define CLEAR "cls"
  #define KEY_UP    72
  #define KEY_DOWN  80
  #define KEY_LEFT  75
  #define KEY_RIGHT 77
  #define KEY_ESC   27
  #define KEY_SPACE 32
  #define KEY_P     112
  #define KEY_R     114
  static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  void gotoxy(int x, int y) {
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hConsole, coord);
  }
  void hideCursor() {
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(hConsole, &ci);
  }
  int getKey() {
    if (_kbhit()) {
      int c = _getch();
      if (c == 0 || c == 224) c = _getch();
      return c;
    }
    return 0;
  }
#else
  #include <ncurses.h>
  #define CLEAR "clear"
  void hideCursor() { curs_set(0); }
  int getKey() {
    int c = getch();
    return (c == ERR) ? 0 : c;
  }
#endif

// ─────────────────────────────────────────────
// СТРУКТУРЫ
// ─────────────────────────────────────────────

struct Config {
    int  cols         = 20;
    int  rows         = 20;
    int  speed_easy   = 200;
    int  speed_medium = 120;
    int  speed_hard   = 60;
    int  food_score   = 10;
    int  init_length  = 3;
};

struct Point {
    int x, y;
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

enum Direction { UP, DOWN, LEFT, RIGHT };
enum Difficulty { EASY, MEDIUM, HARD };
enum GameState  { MENU, PLAYING, PAUSED, GAMEOVER };

// ─────────────────────────────────────────────
// ЗАГРУЗКА CONFIG
// ─────────────────────────────────────────────

Config loadConfig(const std::string& filename) {
    Config cfg;
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "[INFO] config.cfg not found, using defaults.\n";
        return cfg;
    }
    std::string key;
    int val;
    while (f >> key >> val) {
        if      (key == "cols")         cfg.cols         = val;
        else if (key == "rows")         cfg.rows         = val;
        else if (key == "speed_easy")   cfg.speed_easy   = val;
        else if (key == "speed_medium") cfg.speed_medium = val;
        else if (key == "speed_hard")   cfg.speed_hard   = val;
        else if (key == "food_score")   cfg.food_score   = val;
        else if (key == "init_length")  cfg.init_length  = val;
    }
    return cfg;
}

// ─────────────────────────────────────────────
// РЕКОРДЫ
// ─────────────────────────────────────────────

struct Records {
    int easy = 0, medium = 0, hard = 0;
    const std::string file = "records.dat";

    void load() {
        std::ifstream f(file);
        if (f.is_open()) f >> easy >> medium >> hard;
    }
    void save() {
        std::ofstream f(file);
        if (f.is_open()) f << easy << " " << medium << " " << hard;
    }
    int get(Difficulty d) const {
        if (d == EASY)   return easy;
        if (d == MEDIUM) return medium;
        return hard;
    }
    void update(Difficulty d, int score) {
        if (d == EASY   && score > easy)   { easy   = score; save(); }
        if (d == MEDIUM && score > medium) { medium = score; save(); }
        if (d == HARD   && score > hard)   { hard   = score; save(); }
    }
};

// ─────────────────────────────────────────────
// ИГРОВОЕ ПОЛЕ
// ─────────────────────────────────────────────

class Snake {
public:
    Config     cfg;
    Records    rec;
    Difficulty diff  = MEDIUM;
    GameState  state = MENU;

    std::deque<Point> body;
    Direction  dir     = RIGHT;
    Direction  nextDir = RIGHT;
    Point      food    = {0, 0};
    int        score   = 0;
    bool       newRecord = false;

    Snake(Config c) : cfg(c) { rec.load(); }

    void initGame() {
        body.clear();
        int mx = cfg.cols / 2, my = cfg.rows / 2;
        for (int i = 0; i < cfg.init_length; i++)
            body.push_back({mx - i, my});
        dir = RIGHT; nextDir = RIGHT;
        score = 0; newRecord = false;
        placeFood();
        state = PLAYING;
    }

    void placeFood() {
        std::vector<Point> free;
        for (int x = 1; x < cfg.cols - 1; x++)
            for (int y = 1; y < cfg.rows - 1; y++) {
                Point p = {x, y};
                if (std::find(body.begin(), body.end(), p) == body.end())
                    free.push_back(p);
            }
        if (!free.empty())
            food = free[rand() % free.size()];
    }

    bool step() {
        dir = nextDir;
        Point head = body.front();
        switch (dir) {
            case UP:    head.y--; break;
            case DOWN:  head.y++; break;
            case LEFT:  head.x--; break;
            case RIGHT: head.x++; break;
        }
        if (head.x <= 0 || head.x >= cfg.cols - 1 ||
            head.y <= 0 || head.y >= cfg.rows - 1)
            return false;
        for (auto& s : body)
            if (s == head) return false;

        body.push_front(head);

        if (head == food) {
            int mult = (diff == EASY ? 1 : diff == MEDIUM ? 2 : 3);
            score += cfg.food_score * mult;
            placeFood();
        } else {
            body.pop_back();
        }
        return true;
    }

    int getSpeed() const {
        if (diff == EASY)   return cfg.speed_easy;
        if (diff == MEDIUM) return cfg.speed_medium;
        return cfg.speed_hard;
    }

    std::string diffName() const {
        if (diff == EASY)   return "Легкий  ";
        if (diff == MEDIUM) return "Средний ";
        return "Сложный ";
    }
};

// ─────────────────────────────────────────────
// ОТРИСОВКА
// ─────────────────────────────────────────────

#ifdef _WIN32
void draw(const Snake& g) {
    gotoxy(0, 0);
    const int W = g.cfg.cols, H = g.cfg.rows;
    std::string hud = " Счёт: " + std::to_string(g.score)
                    + "  Рекорд: " + std::to_string(g.rec.get(g.diff))
                    + "  Длина: " + std::to_string((int)g.body.size())
                    + "  [" + g.diffName() + "]    ";
    std::cout << hud << "\n";
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            Point p = {x, y};
            if (y == 0 || y == H-1)
                std::cout << (x == 0 || x == W-1 ? '+' : '-');
            else if (x == 0 || x == W-1)
                std::cout << '|';
            else if (p == g.body.front())
                std::cout << '@';
            else if (std::find(g.body.begin()+1, g.body.end(), p) != g.body.end())
                std::cout << 'o';
            else if (p == g.food)
                std::cout << '*';
            else
                std::cout << ' ';
        }
        std::cout << "\n";
    }
    if (g.state == PAUSED)
        std::cout << "\n  *** ПАУЗА — нажмите P/Space для продолжения ***\n";
    else
        std::cout << "\n  Стрелки: движение | P/Space: пауза | R: рестарт | ESC: меню\n";
}
#else
void draw(const Snake& g) {
    clear();
    const int W = g.cfg.cols, H = g.cfg.rows;
    attron(A_BOLD);
    mvprintw(0, 1, "Счёт: %-6d  Рекорд: %-6d  Длина: %-4d  [%s]",
             g.score, g.rec.get(g.diff), (int)g.body.size(),
             g.diffName().c_str());
    attroff(A_BOLD);
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            Point p = {x, y};
            if (y == 0 || y == H-1) {
                attron(COLOR_PAIR(3));
                mvaddch(y+1, x*2, (x == 0 || x == W-1) ? '+' : '-');
                if (x*2+1 < W*2) mvaddch(y+1, x*2+1, '-');
                attroff(COLOR_PAIR(3));
            } else if (x == 0 || x == W-1) {
                attron(COLOR_PAIR(3));
                mvaddch(y+1, x*2, '|');
                attroff(COLOR_PAIR(3));
            } else if (p == g.body.front()) {
                attron(COLOR_PAIR(1) | A_BOLD);
                mvaddch(y+1, x*2, '@');
                attroff(COLOR_PAIR(1) | A_BOLD);
            } else if (std::find(g.body.begin()+1, g.body.end(), p) != g.body.end()) {
                attron(COLOR_PAIR(1));
                mvaddch(y+1, x*2, 'o');
                attroff(COLOR_PAIR(1));
            } else if (p == g.food) {
                attron(COLOR_PAIR(2) | A_BOLD);
                mvaddch(y+1, x*2, '*');
                attroff(COLOR_PAIR(2) | A_BOLD);
            }
        }
    }
    if (g.state == PAUSED) {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(H/2+1, W-2, " *** ПАУЗА *** ");
        attroff(COLOR_PAIR(4) | A_BOLD);
    }
    mvprintw(H+2, 1, "Стрелки: движение | P/Space: пауза | R: рестарт | ESC: меню");
    refresh();
}
#endif

// ─────────────────────────────────────────────
// МЕНЮ
// ─────────────────────────────────────────────

void showMenu(Snake& g) {
    system(CLEAR);
    printf("\n");
    printf("  ╔══════════════════════════════════╗\n");
    printf("  ║        И Г Р А   З М Е Й К А    ║\n");
    printf("  ║             Вариант 15           ║\n");
    printf("  ╠══════════════════════════════════╣\n");
    printf("  ║  Уровень сложности:              ║\n");
    printf("  ║  [1] Легкий   (рекорд: %d)\n", g.rec.easy);
    printf("  ║  [2] Средний  (рекорд: %d)\n", g.rec.medium);
    printf("  ║  [3] Сложный  (рекорд: %d)\n", g.rec.hard);
    printf("  ╠══════════════════════════════════╣\n");
    printf("  ║  [Q] Выход                       ║\n");
    printf("  ╚══════════════════════════════════╝\n\n");
    printf("  Выберите вариант: ");
}

void showGameOver(const Snake& g) {
    printf("\n\n");
    printf("  ╔══════════════════════════════╗\n");
    printf("  ║       ИГРА ОКОНЧЕНА          ║\n");
    printf("  ╠══════════════════════════════╣\n");
    printf("  ║  Счёт:   %d\n", g.score);
    printf("  ║  Рекорд: %d\n", g.rec.get(g.diff));
    printf("  ║  Длина:  %d\n", (int)g.body.size());
    if (g.newRecord)
        printf("  ║  *** НОВЫЙ РЕКОРД! ***       ║\n");
    printf("  ╠══════════════════════════════╣\n");
    printf("  ║  [R] Ещё раз  [M] Меню       ║\n");
    printf("  ╚══════════════════════════════╝\n");
}

// ─────────────────────────────────────────────
// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ: игровой цикл
// ─────────────────────────────────────────────

void runGameLoop(Snake& game) {
    system(CLEAR);
    hideCursor();
#ifndef _WIN32
    nodelay(stdscr, TRUE);
#endif
    while (game.state == PLAYING || game.state == PAUSED) {
        int key = getKey();
#ifdef _WIN32
        if      (key == KEY_UP    && game.dir != DOWN)  game.nextDir = UP;
        else if (key == KEY_DOWN  && game.dir != UP)    game.nextDir = DOWN;
        else if (key == KEY_LEFT  && game.dir != RIGHT) game.nextDir = LEFT;
        else if (key == KEY_RIGHT && game.dir != LEFT)  game.nextDir = RIGHT;
        else if (key == KEY_P || key == KEY_SPACE)
            game.state = (game.state == PLAYING) ? PAUSED : PLAYING;
        else if (key == KEY_R) { game.initGame(); }
        else if (key == KEY_ESC) { game.state = MENU; return; }
#else
        if      (key == KEY_UP    && game.dir != DOWN)  game.nextDir = UP;
        else if (key == KEY_DOWN  && game.dir != UP)    game.nextDir = DOWN;
        else if (key == KEY_LEFT  && game.dir != RIGHT) game.nextDir = LEFT;
        else if (key == KEY_RIGHT && game.dir != LEFT)  game.nextDir = RIGHT;
        else if (key == 'p' || key == 'P' || key == ' ')
            game.state = (game.state == PLAYING) ? PAUSED : PLAYING;
        else if (key == 'r' || key == 'R') { game.initGame(); }
        else if (key == 27) { game.state = MENU; return; }
#endif
        if (game.state == PLAYING) {
            if (!game.step()) {
                int oldRec = game.rec.get(game.diff);
                game.rec.update(game.diff, game.score);
                game.newRecord = (game.score > oldRec);
                game.state = GAMEOVER;
            }
        }
        draw(game);
        std::this_thread::sleep_for(std::chrono::milliseconds(game.getSpeed()));
    }
}

// ─────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────

int main() {
    srand((unsigned)time(nullptr));

#ifndef _WIN32
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN,  COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_CYAN,   COLOR_BLACK);
    init_pair(4, COLOR_RED,    COLOR_BLACK);
    curs_set(0);
#endif

    Config cfg = loadConfig("config.cfg");
    Snake  game(cfg);

    bool running = true;
    while (running) {
        showMenu(game);
        char ch;
        std::cin >> ch;
        switch (ch) {
            case '1': game.diff = EASY;   break;
            case '2': game.diff = MEDIUM; break;
            case '3': game.diff = HARD;   break;
            case 'q': case 'Q': running = false; continue;
            default: continue;
        }
        game.initGame();
        runGameLoop(game);

        while (game.state == GAMEOVER) {
#ifndef _WIN32
            nodelay(stdscr, FALSE);
#endif
            system(CLEAR);
            draw(game);
            showGameOver(game);
            char ans = 0;
            std::cin >> ans;
            if (ans == 'r' || ans == 'R') {
                game.initGame();
#ifndef _WIN32
                nodelay(stdscr, TRUE);
#endif
                runGameLoop(game);
            } else {
                game.state = MENU;
            }
        }
    }

#ifndef _WIN32
    endwin();
#endif
    printf("\nДо свидания!\n");
    return 0;
}
