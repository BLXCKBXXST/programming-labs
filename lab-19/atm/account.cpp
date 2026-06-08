#include "account.h"
#include <stdexcept>
#include <ctime>
#include <cstring>
#include <algorithm>

Account::Account(const std::string& card_number, double initial_balance)
    : card_number_(card_number), balance_(initial_balance) {}

double Account::deposit(double amount) {
    if (amount <= 0) throw std::runtime_error("Сумма пополнения должна быть > 0");
    balance_ += amount;
    Transaction t{};
    t.type          = TransactionType::DEPOSIT;
    t.amount        = amount;
    t.fee           = 0.0;
    t.balance_after = balance_;
    t.timestamp     = std::time(nullptr);
    std::strncpy(t.card_number, card_number_.c_str(), sizeof(t.card_number)-1);
    history_.push_back(t);
    return balance_;
}

double Account::withdraw(double amount) {
    if (amount <= 0)
        throw std::runtime_error("Сумма должна быть > 0");
    if (amount > kMaxSingle)
        throw std::runtime_error("Превышен разовый лимит снятия (10 000 руб)");
    if (todayWithdrawn() + amount > kDailyLimit)
        throw std::runtime_error("Превышен суточный лимит снятия (50 000 руб)");

    double fee = std::max(amount * kFeeRate, kFeeMin);
    double total = amount + fee;
    if (total > balance_)
        throw std::runtime_error("Недостаточно средств (включая комиссию " +
            std::to_string(fee) + " руб)");

    balance_ -= total;
    Transaction t{};
    t.type          = TransactionType::WITHDRAW;
    t.amount        = amount;
    t.fee           = fee;
    t.balance_after = balance_;
    t.timestamp     = std::time(nullptr);
    std::strncpy(t.card_number, card_number_.c_str(), sizeof(t.card_number)-1);
    history_.push_back(t);
    return balance_;
}

std::vector<Transaction> Account::lastTransactions(int n) const {
    if ((int)history_.size() <= n)
        return history_;
    return std::vector<Transaction>(history_.end() - n, history_.end());
}

void Account::applyTransaction(const Transaction& t) {
    balance_ = t.balance_after;
    history_.push_back(t);
}

double Account::todayWithdrawn() const {
    std::time_t now = std::time(nullptr);
    struct tm* lt   = std::localtime(&now);
    lt->tm_hour = 0; lt->tm_min = 0; lt->tm_sec = 0;
    std::time_t today = std::mktime(lt);

    double total = 0.0;
    for (const auto& tr : history_) {
        if (tr.type == TransactionType::WITHDRAW && tr.timestamp >= today)
            total += tr.amount;
    }
    return total;
}
