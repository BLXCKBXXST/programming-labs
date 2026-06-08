#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../account.h"
#include <stdexcept>

TEST_CASE("Deposit increases balance") {
    Account a("1234567890123456", 1000.0);
    double b = a.deposit(500.0);
    CHECK(b == doctest::Approx(1500.0));
    CHECK(a.balance() == doctest::Approx(1500.0));
}

TEST_CASE("Withdraw with fee") {
    Account a("1234567890123456", 10000.0);
    // 1000 руб: fee = max(10, 30) = 30 руб
    double b = a.withdraw(1000.0);
    CHECK(b == doctest::Approx(10000.0 - 1000.0 - 30.0));
}

TEST_CASE("Withdraw fee 1pct when > 3000") {
    Account a("1234567890123456", 20000.0);
    // 5000 руб: fee = max(50, 30) = 50 руб
    double b = a.withdraw(5000.0);
    CHECK(b == doctest::Approx(20000.0 - 5000.0 - 50.0));
}

TEST_CASE("Withdraw exceeds single limit") {
    Account a("1234567890123456", 100000.0);
    CHECK_THROWS_AS(a.withdraw(10001.0), std::runtime_error);
}

TEST_CASE("Withdraw insufficient funds") {
    Account a("1234567890123456", 100.0);
    CHECK_THROWS_AS(a.withdraw(500.0), std::runtime_error);
}

TEST_CASE("lastTransactions returns max 5") {
    Account a("1234567890123456", 100000.0);
    for (int i = 0; i < 7; ++i) a.deposit(100.0);
    auto txs = a.lastTransactions(5);
    CHECK(txs.size() == 5);
}
