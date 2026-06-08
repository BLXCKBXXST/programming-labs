#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../journal.h"
#include "../transaction.h"
#include <cstdio>
#include <cstring>

TEST_CASE("Journal append and read") {
    const char* path = "/tmp/test_journal_lab19.bin";
    std::remove(path);
    {
        Journal j(path);
        Transaction t{};
        t.type          = TransactionType::DEPOSIT;
        t.amount        = 500.0;
        t.fee           = 0.0;
        t.balance_after = 1500.0;
        t.timestamp     = 1700000000;
        std::strncpy(t.card_number, "1234567890123456", 19);
        j.append(t);
    }
    {
        Journal j(path);
        auto all = j.readAll();
        REQUIRE(all.size() == 1);
        CHECK(all[0].type   == TransactionType::DEPOSIT);
        CHECK(all[0].amount == doctest::Approx(500.0));
    }
    std::remove(path);
}

TEST_CASE("Journal append-only: multiple records") {
    const char* path = "/tmp/test_journal_lab19_multi.bin";
    std::remove(path);
    for (int i = 0; i < 5; ++i) {
        Journal j(path);  // открываем заново каждый раз (как после краша)
        Transaction t{};
        t.type          = TransactionType::WITHDRAW;
        t.amount        = (double)(i+1) * 100;
        t.fee           = 30.0;
        t.balance_after = 10000.0 - (double)(i+1)*130;
        t.timestamp     = 1700000000 + i;
        std::strncpy(t.card_number, "1234567890123456", 19);
        j.append(t);
    }
    Journal j(path);
    auto all = j.readAll();
    CHECK(all.size() == 5);
    std::remove(path);
}
