#include "atm_engine.h"
#include <iostream>
#include <filesystem>

int main() {
    // Данные хранятся рядом с исполняемым файлом в папке data/
    std::string data_dir = "data";
    try {
        AtmEngine atm(data_dir);
        atm.run();
    } catch (const std::exception& e) {
        std::cerr << "[FATAL] " << e.what() << "\n";
        return 1;
    }
    return 0;
}
