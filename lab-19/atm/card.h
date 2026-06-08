#pragma once
#include <string>

class Card {
public:
    Card() = default;
    Card(const std::string& number, const std::string& pin_hash);

    const std::string& number()   const { return number_; }
    bool  isBlocked()             const { return blocked_; }
    void  block()                       { blocked_ = true; }

    // Проверяет PIN (сравнивает хэш). Возвращает true при совпадении.
    bool  checkPin(const std::string& pin) const;

    // Сбрасывает счётчик попыток (успешный вход)
    void  resetAttempts()               { attempts_ = 0; }

    // Добавляет попытку; возвращает оставшееся число попыток (0 → карта заблокирована)
    int   addFailedAttempt();

    int   failedAttempts()  const { return attempts_; }

private:
    std::string number_;
    std::string pin_hash_;   // SHA-256 (hex) или простой hash для демо
    bool        blocked_  = false;
    int         attempts_ = 0;

    static std::string hashPin(const std::string& pin);
};
