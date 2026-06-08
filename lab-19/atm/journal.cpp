#include "journal.h"
#include <stdexcept>
#include <iostream>

Journal::Journal(const std::string& path) : path_(path) {
    openAppend();
}

Journal::~Journal() {
    if (out_.is_open()) out_.close();
}

void Journal::openAppend() {
    out_.open(path_, std::ios::binary | std::ios::app);
    if (!out_.is_open())
        throw std::runtime_error("Не удалось открыть журнал: " + path_);
}

void Journal::append(const Transaction& t) {
    out_.write(reinterpret_cast<const char*>(&t), sizeof(Transaction));
    out_.flush();  // важно: сбрасываем буфер после каждой записи
    if (out_.fail())
        throw std::runtime_error("Ошибка записи в журнал");
}

std::vector<Transaction> Journal::readAll() const {
    std::vector<Transaction> result;
    std::ifstream in(path_, std::ios::binary);
    if (!in.is_open()) return result;  // файла нет — первый запуск

    Transaction t{};
    while (in.read(reinterpret_cast<char*>(&t), sizeof(Transaction))) {
        result.push_back(t);
    }
    // Если read не прочитал полный sizeof(Transaction) — хвостовой мусор,
    // просто игнорируем (частичная запись при краше)
    return result;
}
