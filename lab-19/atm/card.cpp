#include "card.h"
#include <functional>   // std::hash (простой, не криптографический)
#include <sstream>
#include <iomanip>

// Простой хэш для учебного проекта (не для продакшена!)
std::string Card::hashPin(const std::string& pin) {
    std::size_t h = std::hash<std::string>{}(pin + "atm_salt_2024");
    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << h;
    return oss.str();
}

Card::Card(const std::string& number, const std::string& pin_hash)
    : number_(number), pin_hash_(pin_hash) {}

bool Card::checkPin(const std::string& pin) const {
    return pin_hash_ == hashPin(pin);
}

int Card::addFailedAttempt() {
    ++attempts_;
    if (attempts_ >= 3) {
        blocked_ = true;
        return 0;
    }
    return 3 - attempts_;
}

// Фабрика: создать карту с открытым PIN (хэшируется здесь)
Card makeCard(const std::string& number, const std::string& plain_pin) {
    // Используем тот же hashPin через дружественный вызов
    // Пробрасываем через временный объект
    Card tmp;
    // Создаём через конструктор с уже захэшированным PIN
    // (нужна вспомогательная функция)
    return Card(number, 
        [&]() -> std::string {
            std::size_t h = std::hash<std::string>{}(plain_pin + "atm_salt_2024");
            std::ostringstream oss;
            oss << std::hex << std::setw(16) << std::setfill('0') << h;
            return oss.str();
        }()
    );
}
