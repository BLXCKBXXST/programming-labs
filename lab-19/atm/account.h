#pragma once
#include <string>
#include <vector>
#include "transaction.h"

class Account {
public:
    Account() = default;
    Account(const std::string& card_number, double initial_balance = 0.0);

    const std::string& cardNumber()  const { return card_number_; }
    double             balance()     const { return balance_; }

    // Пополнение. Возвращает новый баланс.
    double deposit(double amount);

    // Снятие с комиссией 1% (min 30 руб).
    // Выбрасывает std::runtime_error при нарушении лимитов.
    double withdraw(double amount);

    // Последние N транзакций (для экрана истории)
    std::vector<Transaction> lastTransactions(int n = 5) const;

    // Применить транзакцию из журнала (для recovery)
    void applyTransaction(const Transaction& t);

    // Суточная сумма снятий (для проверки суточного лимита)
    double todayWithdrawn() const;

private:
    std::string              card_number_;
    double                   balance_      = 0.0;
    std::vector<Transaction> history_;     // полная история в памяти

    static constexpr double kMaxSingle     = 10'000.0;
    static constexpr double kDailyLimit    = 50'000.0;
    static constexpr double kFeeRate       = 0.01;
    static constexpr double kFeeMin        = 30.0;
};
