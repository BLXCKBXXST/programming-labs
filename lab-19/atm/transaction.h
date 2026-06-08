#pragma once
#include <cstdint>
#include <ctime>

enum class TransactionType : uint8_t {
    DEPOSIT    = 1,
    WITHDRAW   = 2,
    CHECK      = 3
};

struct Transaction {
    TransactionType type;
    double          amount;      // всегда >= 0
    double          fee;         // комиссия (только для WITHDRAW)
    double          balance_after;
    std::time_t     timestamp;
    char            card_number[20];
};
