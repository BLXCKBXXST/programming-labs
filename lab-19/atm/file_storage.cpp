#include "file_storage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <iostream>

namespace fs = std::filesystem;

std::string FileStorage::hashPin(const std::string& pin) {
    std::size_t h = std::hash<std::string>{}(pin + "atm_salt_2024");
    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << h;
    return oss.str();
}

FileStorage::FileStorage(const std::string& data_dir) : data_dir_(data_dir) {
    fs::create_directories(data_dir);
}

bool FileStorage::loadCard(const std::string& number, Card& out) const {
    std::ifstream f(cardsPath());
    if (!f) return false;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string num, hash, blk;
        std::getline(ss, num,  ':');
        std::getline(ss, hash, ':');
        std::getline(ss, blk,  ':');
        if (num == number) {
            out = Card(num, hash);
            if (blk == "1") out.block();
            return true;
        }
    }
    return false;
}

void FileStorage::saveCard(const Card& card) const {
    // Читаем всё, заменяем нужную строку
    std::ifstream in(cardsPath());
    std::ostringstream buf;
    bool found = false;
    if (in) {
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line[0] != '#') {
                std::istringstream ss(line);
                std::string num;
                std::getline(ss, num, ':');
                if (num == card.number()) {
                    // нам нужен hash — читаем из текущей строки
                    std::string hash, blk;
                    std::getline(ss, hash, ':');
                    buf << num << ':' << hash << ':'
                        << (card.isBlocked() ? '1' : '0') << '\n';
                    found = true;
                    continue;
                }
            }
            buf << line << '\n';
        }
    }
    if (!found) {
        // Новая карта — PIN hash неизвестен здесь; добавляем с пустым hash
        // (при нормальном flow createDemoDataIfNeeded уже создал записи)
        buf << card.number() << ":" << "" << ":"
            << (card.isBlocked() ? '1' : '0') << '\n';
    }
    in.close();
    std::ofstream out(cardsPath());
    out << buf.str();
}

bool FileStorage::loadAccount(const std::string& card_number, Account& out) const {
    std::ifstream f(accountsPath());
    if (!f) return false;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string num, bal;
        std::getline(ss, num, ':');
        std::getline(ss, bal, ':');
        if (num == card_number) {
            try { out = Account(num, std::stod(bal)); }
            catch (...) { out = Account(num, 0.0); }
            return true;
        }
    }
    return false;
}

void FileStorage::saveAccount(const Account& acc) const {
    std::ifstream in(accountsPath());
    std::ostringstream buf;
    bool found = false;
    if (in) {
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line[0] != '#') {
                std::istringstream ss(line);
                std::string num;
                std::getline(ss, num, ':');
                if (num == acc.cardNumber()) {
                    buf << num << ':' << std::fixed
                        << std::setprecision(2) << acc.balance() << '\n';
                    found = true;
                    continue;
                }
            }
            buf << line << '\n';
        }
    }
    if (!found)
        buf << acc.cardNumber() << ':'
            << std::fixed << std::setprecision(2) << acc.balance() << '\n';
    in.close();
    std::ofstream out(accountsPath());
    out << buf.str();
}

void FileStorage::createDemoDataIfNeeded() const {
    if (!fs::exists(cardsPath())) {
        std::ofstream f(cardsPath());
        // Демо-карты: номер:pin_hash:blocked
        // PIN 1234 → hashPin("1234")
        // PIN 5678 → hashPin("5678")
        f << "# number:pin_hash:blocked(0/1)\n";
        f << "1234567890123456:" << hashPin("1234") << ":0\n";
        f << "9876543210987654:" << hashPin("5678") << ":0\n";
        std::cout << "[Init] Созданы демо-карты: 1234567890123456 (PIN 1234), "
                     "9876543210987654 (PIN 5678)\n";
    }
    if (!fs::exists(accountsPath())) {
        std::ofstream f(accountsPath());
        f << "# card_number:balance\n";
        f << "1234567890123456:50000.00\n";
        f << "9876543210987654:10000.00\n";
        std::cout << "[Init] Созданы демо-счета.\n";
    }
}
