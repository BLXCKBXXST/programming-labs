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
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// ─── ANSI escape helpers ───────────────────────────────────────────
#define CLR       "\033[2J\033[H"
#define HOME      "\033[H"
#define HIDE_CUR  "\033[?25l"
#define SHOW_CUR  "\033[?25h"
#define BOLD      "\033[1m"
#define RESET     "\033[0m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define CYAN      "\033[36m"
#define RED       "\033[31m"
#define WHITE     "\033[37m"
#define GRAY      "\033[90m"

// ─── Неблокирующий ввод (POSIX) ───────────────────────────────────
static struct termios orig_termios;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    printf(SHOW_CUR);
}

// Стрелки: UP=1001 DOWN=1002 LEFT=1003 RIGHT=1004
int readKey() {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) != 1) return 0;
    if (c == '\033') {
        char seq[3] = {0};
        read(STDIN_FILENO, &seq[0], 1);
        read(STDIN_FILENO, &seq[1], 1);
        if (seq[0] == '[') {
            if (seq[1] == 'A') return 1001;
            if (seq[1] == 'B') return 1002;
            if (seq[1] == 'D') return 1003;
            if (seq[1] == 'C') return 1004;
        }
        return 27;
    }
    return (unsigned char)c;
}

// ─── Структуры ────────────────────────────────────────────────────

struct Config {
    int cols         = 20;
    int rows         = 20;
    int speed_easy   = 200;
    int speed_medium = 120;
    int speed_hard   = 60;
    int food_score   = 10;
    int init_length  = 3;
};

Config loadConfig(const std::string& fn) {
    Config c;
    std::ifstream f(fn);
    if (!f.is_open()) return c;
    std::string key; int val;
    while (f >> key >> val) {
        if      (key == "cols")         c.cols         = val;
        else if (key == "rows")         c.rows         = val;
        else if (key == "speed_easy")   c.speed_easy   = val;
        else if (key == "speed_medium") c.speed_medium = val;
        else if (key == "speed_hard")   c.speed_hard   = val;
        else if (key == "food_score")   c.food_score   = val;
        else if (key == "init_length")  c.init_length  = val;
    }
    return c;
}

struct Point {
    int x, y;
    bool operator==(const Point& o) const { return x==o.x && y==o.y; }
};

enum Dir   { DUP, DDOWN, DLEFT, DRIGHT };
enum Diff  { EASY, MEDIUM, HARD };
enum State { MENU, PLAYING, PAUSED, GAMEOVER };

struct Records {
    int v[3] = {0, 0, 0};
    const char* file = "records.dat";
    void load() {
        std::ifstream f(file);
        if (f.is_open()) f >> v[0] >> v[1] >> v[2];
    }
    void save() {
        std::ofstream f(file);
        if (f.is_open()) f << v[0] << " " << v[1] << " " << v[2];
    }
    int  get(Diff d) const { return v[(int)d]; }
    bool update(Diff d, int s) {
        if (s > v[(int)d]) { v[(int)d]=s; save(); return true; }
        return false;
    }
};

// ─── Игра ─────────────────────────────────────────────────────────

struct Game {
    Config cfg;
    Records rec;
    Diff   diff  = MEDIUM;
    State  state = MENU;
    std::deque<Point> body;
    Dir    dir = DRIGHT, nextDir = DRIGHT;
    Point  food = {0,0};
    int    score = 0;
    bool   newRec = false;

    Game(Config c) : cfg(c) { rec.load(); }

    void init() {
        body.clear();
        int mx = cfg.cols/2, my = cfg.rows/2;
        for (int i = 0; i < cfg.init_length; i++)
            body.push_back({mx-i, my});
        dir = DRIGHT; nextDir = DRIGHT;
        score = 0; newRec = false;
        placeFood(); state = PLAYING;
    }

    void placeFood() {
        std::vector<Point> free;
        for (int x=1; x<cfg.cols-1; x++)
            for (int y=1; y<cfg.rows-1; y++) {
                Point p={x,y};
                if (std::find(body.begin(),body.end(),p)==body.end())
                    free.push_back(p);
            }
        if (!free.empty()) food = free[rand()%free.size()];
    }

    bool step() {
        dir = nextDir;
        Point h = body.front();
        if (dir==DUP)    h.y--;
        if (dir==DDOWN)  h.y++;
        if (dir==DLEFT)  h.x--;
        if (dir==DRIGHT) h.x++;
        if (h.x<=0||h.x>=cfg.cols-1||h.y<=0||h.y>=cfg.rows-1) return false;
        for (auto& s : body) if (s==h) return false;
        body.push_front(h);
        if (h==food) {
            int m = (diff==EASY?1:diff==MEDIUM?2:3);
            score += cfg.food_score * m;
            placeFood();
        } else {
            body.pop_back();
        }
        return true;
    }

    int speed() const {
        if (diff==EASY)   return cfg.speed_easy;
        if (diff==MEDIUM) return cfg.speed_medium;
        return cfg.speed_hard;
    }
    const char* diffName() const {
        if (diff==EASY)   return "Legkiy  ";
        if (diff==MEDIUM) return "Sredniy ";
        return "Slozhnyy";
    }
};

// ─── Отрисовка ────────────────────────────────────────────────────

void drawGame(const Game& g) {
    printf(HOME);
    const int W = g.cfg.cols, H = g.cfg.rows;

    // HUD
    printf(BOLD WHITE " Score: %-6d  Record: %-6d  Len: %-4d  [%s]" RESET "     \n",
           g.score, g.rec.get(g.diff), (int)g.body.size(), g.diffName());

    for (int y = 0; y < H; y++) {
        printf(" ");
        for (int x = 0; x < W; x++) {
            Point p = {x,y};
            if (y==0||y==H-1) {
                printf(CYAN "%c" RESET, (x==0||x==W-1)?'+':'-');
            } else if (x==0||x==W-1) {
                printf(CYAN "|" RESET);
            } else if (p==g.body.front()) {
                printf(BOLD GREEN "@" RESET);
            } else if (std::find(g.body.begin()+1,g.body.end(),p)!=g.body.end()) {
                printf(GREEN "o" RESET);
            } else if (p==g.food) {
                printf(BOLD YELLOW "*" RESET);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    if (g.state==PAUSED)
        printf(BOLD RED "\n  *** PAUZA — nazhmi P/Space ***" RESET "\n");
    else
        printf(GRAY "\n  Arrows:move  P:pause  R:restart  ESC:menu" RESET "\n");
    fflush(stdout);
}

void drawMenu(const Game& g) {
    printf(CLR);
    printf("\n");
    printf("  +----------------------------------+\n");
    printf("  |   IGRA  ZMEYKA  (Variant 15)    |\n");
    printf("  +----------------------------------+\n");
    printf("  |  Uroven slozhnosti:              |\n");
    printf("  |  [1] Legkiy    rekord: %-5d     |\n", g.rec.v[0]);
    printf("  |  [2] Sredniy   rekord: %-5d     |\n", g.rec.v[1]);
    printf("  |  [3] Slozhnyy  rekord: %-5d     |\n", g.rec.v[2]);
    printf("  +----------------------------------+\n");
    printf("  |  [Q] Vyhod                       |\n");
    printf("  +----------------------------------+\n\n");
    printf("  Vash vybor: ");
    fflush(stdout);
}

void drawGameOver(const Game& g) {
    printf("\n");
    printf("  +------------------------------+\n");
    printf("  |      IGRA  OKONCHENA         |\n");
    printf("  +------------------------------+\n");
    printf("  |  Schet:   %-6d             |\n", g.score);
    printf("  |  Rekord:  %-6d             |\n", g.rec.get(g.diff));
    printf("  |  Dlina:   %-6d             |\n", (int)g.body.size());
    if (g.newRec)
        printf("  |  *** NOVYY REKORD! ***       |\n");
    printf("  +------------------------------+\n");
    printf("  |  [R] Eshcho raz  [M] Menyu   |\n");
    printf("  +------------------------------+\n");
    fflush(stdout);
}

// ─── Игровой цикл ─────────────────────────────────────────────────

void runLoop(Game& g) {
    printf(CLR HIDE_CUR);
    fflush(stdout);
    while (g.state==PLAYING || g.state==PAUSED) {
        int k = readKey();
        if      (k==1001 && g.dir!=DDOWN)  g.nextDir = DUP;
        else if (k==1002 && g.dir!=DUP)    g.nextDir = DDOWN;
        else if (k==1003 && g.dir!=DRIGHT) g.nextDir = DLEFT;
        else if (k==1004 && g.dir!=DLEFT)  g.nextDir = DRIGHT;
        else if (k=='p'||k=='P'||k==' ')
            g.state = (g.state==PLAYING) ? PAUSED : PLAYING;
        else if (k=='r'||k=='R') { g.init(); }
        else if (k==27) { g.state=MENU; return; }

        if (g.state==PLAYING) {
            if (!g.step()) {
                g.newRec = g.rec.update(g.diff, g.score);
                g.state = GAMEOVER;
            }
        }
        drawGame(g);
        std::this_thread::sleep_for(std::chrono::milliseconds(g.speed()));
    }
}

// ─── main ─────────────────────────────────────────────────────────

int main() {
    srand((unsigned)time(nullptr));
    enableRawMode();
    atexit(disableRawMode);

    Config cfg = loadConfig("config.cfg");
    Game game(cfg);

    bool running = true;
    while (running) {
        disableRawMode();
        drawMenu(game);

        char ch = 0;
        if (read(STDIN_FILENO, &ch, 1) != 1) ch = 'q';
        enableRawMode();

        switch(ch) {
            case '1': game.diff = EASY;   break;
            case '2': game.diff = MEDIUM; break;
            case '3': game.diff = HARD;   break;
            case 'q': case 'Q': running = false; continue;
            default: continue;
        }
        game.init();
        runLoop(game);

        while (game.state == GAMEOVER) {
            disableRawMode();
            printf(CLR);
            drawGame(game);
            drawGameOver(game);
            char ans = 0;
            if (read(STDIN_FILENO, &ans, 1) != 1) ans = 'm';
            enableRawMode();
            if (ans=='r'||ans=='R') {
                game.init();
                runLoop(game);
            } else {
                game.state = MENU;
            }
        }
    }

    printf(CLR SHOW_CUR);
    printf("Do svidaniya!\n");
    return 0;
}
