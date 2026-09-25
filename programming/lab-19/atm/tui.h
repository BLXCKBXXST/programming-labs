#pragma once
// TUI helpers: ANSI escape, box drawing, raw input
#include <iostream>
#include <sstream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

namespace tui {

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
constexpr const char* BG_CYAN = "\033[46m";

inline void clearScreen() { std::cout << "\033[2J\033[H"; }
inline void hideCursor()  { std::cout << "\033[?25l"; }
inline void showCursor()  { std::cout << "\033[?25h"; }

constexpr int W = 46;

// stripAnsi: removes ANSI escapes, counts only leading UTF-8 bytes
// so Cyrillic/emoji don't add phantom width
inline int visWidth(const std::string& s) {
    int n = 0;
    bool esc = false;
    for (unsigned char c : s) {
        if (c == '\033') { esc = true; continue; }
        if (esc) { if (c == 'm') esc = false; continue; }
        if ((c & 0xC0) != 0x80) ++n; // count only leading UTF-8 bytes
    }
    return n;
}

inline std::string center(const std::string& s, int width, char fill = ' ') {
    int pad = width - visWidth(s);
    if (pad <= 0) return s;
    int left = pad / 2;
    return std::string(left, fill) + s + std::string(pad - left, fill);
}

inline std::string ljust(const std::string& s, int width) {
    int vw = visWidth(s);
    if (vw >= width) return s;
    return s + std::string(width - vw, ' ');
}

// Box drawing — ASCII only (no multi-char literals)
inline void boxTop(int w = W)   { std::cout << CYAN << "+" << std::string(w, '-') << "+" << RESET << "\n"; }
inline void boxBot(int w = W)   { std::cout << CYAN << "+" << std::string(w, '-') << "+" << RESET << "\n"; }
inline void boxSep(int w = W)   { std::cout << CYAN << "+" << std::string(w, '-') << "+" << RESET << "\n"; }
inline void boxEmpty(int w = W) { std::cout << CYAN << "|" << std::string(w, ' ') << "|" << RESET << "\n"; }
inline void boxRow(const std::string& content, int w = W) {
    int pad = w - visWidth(content);
    if (pad < 0) pad = 0;
    std::cout << CYAN << "|" << RESET
              << content << std::string(pad, ' ')
              << CYAN << "|" << RESET << "\n";
}

// Raw single-char read (no Enter)
inline char readRawChar() {
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

// PIN input (masked)
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
            std::cout << YELLOW << '*' << RESET << std::flush;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << "\n";
    return pin;
}

// Numeric menu — draws items inside an already-open box, closes it itself
inline int simpleMenu(const std::vector<std::string>& items) {
    for (size_t i = 0; i < items.size(); ++i) {
        std::ostringstream line;
        line << "  " << (i + 1) << ". " << items[i];
        boxRow(line.str());
    }
    boxSep();
    boxRow(std::string(DIM) + "  Введите номер пункта" + RESET);
    boxBot();
    showCursor();
    while (true) {
        std::cout << "  " << CYAN << "> " << RESET << std::flush;
        int choice = -1;
        if (std::cin >> choice && choice >= 1 && choice <= (int)items.size()) {
            std::cin.ignore(10000, '\n');
            return choice - 1;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << RED << "  Неверный выбор, попробуйте снова.\n" << RESET;
    }
}

// waitKey — renamed from pause() to avoid conflict with POSIX ::pause()
inline void waitKey(const std::string& msg = "Нажмите любую клавишу...") {
    std::cout << DIM << "  " << msg << RESET << "\n";
    readRawChar();
}

} // namespace tui
