#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "account.h"
#include <stdexcept>

TEST_CASE("Account deposit") {
    Account a("1111222233334444", 1000.0);
    double bal = a.deposit(500.0);
    CHECK(bal == doctest::Approx(1500.0));
    CHECK(a.balance() == doctest::Approx(1500.0));
}

TEST_CASE("Account withdraw with fee") {
    Account a("1111222233334444", 5000.0);
    // withdraw 1000: fee = max(10, 30) = 30, total = 1030
    double bal = a.withdraw(1000.0);
    CHECK(bal == doctest::Approx(3970.0));
}

TEST_CASE("Account withdraw min fee 30") {
    Account a("1111222233334444", 5000.0);
    // withdraw 100: fee = max(1, 30) = 30, total = 130
    double bal = a.withdraw(100.0);
    CHECK(bal == doctest::Approx(4870.0));
}

TEST_CASE("Account withdraw over limit throws") {
    Account a("1111222233334444", 50000.0);
    CHECK_THROWS_AS(a.withdraw(10001.0), std::runtime_error);
}

TEST_CASE("Account insufficient funds throws") {
    Account a("1111222233334444", 100.0);
    CHECK_THROWS_AS(a.withdraw(200.0), std::runtime_error);
}
