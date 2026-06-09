#pragma once
#include <string>

class Card {
public:
    Card() = default;
    Card(const std::string& number, const std::string& pin_hash);

    const std::string& number()   const { return number_; }
    bool  isBlocked()             const { return blocked_; }
    void  block()                       { blocked_ = true; }

    bool  checkPin(const std::string& pin) const;
    void  resetAttempts()               { attempts_ = 0; }
    int   addFailedAttempt();
    int   failedAttempts()  const { return attempts_; }

private:
    std::string number_;
    std::string pin_hash_;
    bool        blocked_  = false;
    int         attempts_ = 0;

    static std::string hashPin(const std::string& pin);
};

// Factory: creates Card with plain PIN (hashes it internally)
Card makeCard(const std::string& number, const std::string& plain_pin);
