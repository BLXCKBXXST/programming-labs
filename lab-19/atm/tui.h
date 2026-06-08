#pragma once
// ─────────────────────────────────────────────────────────────────────────────
// TUI helpers: ANSI escape коды, псевдографика, ввод без эха
// ─────────────────────────────────────────────────────────────────────────────
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <termios.h>
#include <unistd.h>

namespace tui {

// ── Цвета / стили ────────────────────────────────────────────────────────────
constexpr const char* RESET   = "\033[0m";
constexpr const char* BOLD    = "\033[1m";
constexpr const char* DIM     = "\033[2m";
constexpr const char* BLACK   = "\033[30m";
constexpr const char* RED     = "\033[91m";
constexpr const char* GREEN   = "\033[92m";
constexpr const char* YELLOW  = "\033[93m";
constexpr const char* BLUE    = "\033[94m";
constexpr const char* MAGENTA = "\033[95m";
constexpr const char* CYAN    = "\033[96m";
constexpr const char* WHITE   = "\033[97m";
constexpr const char* BG_BLUE = "\033[44m";
constexpr const char* BG_CYAN = "\033[46m";
constexpr const char* BG_DARK = "\033[40m";
constexpr const char* BG_GREEN= "\033[42m";
constexpr const char* BG_RED  = "\033[41m";

// ── Управление курсором ──────────────────────────────────────────────────────
inline void clearScreen()  { std::cout << "\033[2J\033[H";        }
inline void moveTo(int r, int c) { std::cout << "\033[" << r << ";" << c << "H"; }
inline void hideCursor()   { std::cout << "\033[?25l";           }
inline void showCursor()   { std::cout << "\033[?25h";           }
inline void saveCursor()   { std::cout << "\033[s";              }
inline void restoreCursor(){ std::cout << "\033[u";              }

// ── Ширина виджета банкомата ─────────────────────────────────────────────────
constexpr int W = 46;   // внутренняя ширина (без рамки)

// ── Утилиты строк ────────────────────────────────────────────────────────────
inline std::string center(const std::string& s, int width, char fill = ' ') {
    int pad = width - (int)s.size();
    if (pad <= 0) return s.substr(0, width);
    int left = pad / 2;
    return std::string(left, fill) + s + std::string(pad - left, fill);
}
inline std::string ljust(const std::string& s, int width) {
    if ((int)s.size() >= width) return s.substr(0, width);
    return s + std::string(width - s.size(), ' ');
}

// ── Рамка ────────────────────────────────────────────────────────────────────
inline void boxTop(int w = W) {
    std::cout << CYAN << "╔" << std::string(w, '═') << "╗" << RESET << "\n";
}
inline void boxBot(int w = W) {
    std::cout << CYAN << "╚" << std::string(w, '═') << "╝" << RESET << "\n";
}
inline void boxSep(int w = W) {
    std::cout << CYAN << "╠" << std::string(w, '═') << "╣" << RESET << "\n";
}
inline void boxRow(const std::string& content, int w = W) {
    // content уже окрашен; считаем видимую ширину без escape-последовательностей
    // Простое приближение: strip ANSI для подсчёта
    std::string vis;
    bool esc = false;
    for (char c : content) {
        if (c == '\033') { esc = true; continue; }
        if (esc) { if (c == 'm') esc = false; continue; }
        vis += c;
    }
    int pad = w - (int)vis.size();
    if (pad < 0) pad = 0;
    std::cout << CYAN << "║" << RESET
              << content << std::string(pad, ' ')
              << CYAN << "║" << RESET << "\n";
}
inline void boxEmpty(int w = W) {
    std::cout << CYAN << "║" << std::string(w, ' ') << "║" << RESET << "\n";
}

// ── PIN-ввод без эха ─────────────────────────────────────────────────────────
inline std::string readPin(const std::string& prompt, int maxlen = 4) {
    std::cout << prompt << std::flush;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string pin;
    while ((int)pin.size() < maxlen) {
        char c = 0;
        if (read(STDIN_FILENO, &c, 1) <= 0) break;
        if (c == '\n' || c == '\r') break;
        if ((c == 127 || c == '\b') && !pin.empty()) {
            pin.pop_back();
            std::cout << "\b \b" << std::flush;
            continue;
        }
        if (c >= '0' && c <= '9') {
            pin += c;
            std::cout << YELLOW << "●" << RESET << std::flush;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << "\n";
    return pin;
}

// ── Чтение одного символа без Enter ─────────────────────────────────────────
inline char readChar() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c = 0;
    read(STDIN_FILENO, &c, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

// ── Меню со стрелками ────────────────────────────────────────────────────────
// items: { "текст", ... }; возвращает индекс выбранного пункта (или -1 если ESC)
inline int arrowMenu(const std::vector<std::string>& items, int selected = 0) {
    hideCursor();
    int cur = selected;
    while (true) {
        // Перерисовываем пункты (курсор уже на нужной позиции снаружи)
        for (int i = 0; i < (int)items.size(); ++i) {
            if (i == cur) {
                boxRow(std::string(BG_CYAN) + BLACK + BOLD + " ▶  " + ljust(items[i], W-5) + RESET);
            } else {
                boxRow(std::string("   ") + " " + ljust(items[i], W-4));
            }
        }
        std::cout << std::flush;

        // Перемещаем курсор назад вверх для следующего цикла
        std::cout << "\033[" << items.size() << "A";

        // Читаем клавишу
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        char c = 0;
        read(STDIN_FILENO, &c, 1);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        if (c == 27) {  // ESC или стрелка
            char seq[2] = {};
            // non-blocking read
            struct termios t2 = oldt;
            t2.c_cc[VMIN]  = 0;
            t2.c_cc[VTIME] = 1;
            tcsetattr(STDIN_FILENO, TCSANOW, &t2);
            if (read(STDIN_FILENO, &seq[0], 1) > 0 && seq[0] == '[') {
                read(STDIN_FILENO, &seq[1], 1);
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                if (seq[1] == 'A') { cur = (cur - 1 + (int)items.size()) % (int)items.size(); } // вверх
                else if (seq[1] == 'B') { cur = (cur + 1) % (int)items.size(); }                // вниз
            } else {
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                // Чистый ESC
                std::cout << "\033[" << items.size() << "B";
                showCursor();
                return -1;
            }
        } else if (c == '\n' || c == '\r' || c == ' ') {
            std::cout << "\033[" << items.size() << "B";
            showCursor();
            return cur;
        } else if (c >= '1' && c <= '9') {
            int idx = c - '1';
            if (idx < (int)items.size()) {
                cur = idx;
                std::cout << "\033[" << items.size() << "B";
                showCursor();
                return cur;
            }
        }
    }
}

// ── Пауза ────────────────────────────────────────────────────────────────────
inline void pause(const std::string& msg = "Нажмите любую клавишу...") {
    std::cout << "\n";
    boxRow(std::string(DIM) + center(msg, W) + RESET);
    boxBot();
    readChar();
}

} // namespace tui
