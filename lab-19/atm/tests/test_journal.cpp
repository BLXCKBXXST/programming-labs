#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "journal.h"
#include "transaction.h"
#include <cstdio>
#include <cstring>

static const char* TMP = "/tmp/test_journal.bin";

TEST_CASE("Journal append and read back") {
    std::remove(TMP);
    {
        Journal j(TMP);
        Transaction t{};
        t.type = TransactionType::DEPOSIT;
        t.amount = 500.0;
        t.fee = 0.0;
        t.balance_after = 1500.0;
        t.timestamp = 1000000;
        std::strncpy(t.card_number, "1111", sizeof(t.card_number)-1);
        j.append(t);
    }
    // re-open and read
    Journal j2(TMP);
    auto records = j2.readAll();
    REQUIRE(records.size() == 1);
    CHECK(records[0].type == TransactionType::DEPOSIT);
    CHECK(records[0].amount == doctest::Approx(500.0));
    CHECK(records[0].balance_after == doctest::Approx(1500.0));
    std::remove(TMP);
}

TEST_CASE("Journal append-only: multiple records") {
    std::remove(TMP);
    Journal j(TMP);
    for (int i = 0; i < 5; ++i) {
        Transaction t{};
        t.type = TransactionType::WITHDRAW;
        t.amount = (double)(i + 1) * 100.0;
        t.fee = 30.0;
        t.balance_after = 5000.0 - (i + 1) * 130.0;
        t.timestamp = 1000000 + i;
        std::strncpy(t.card_number, "1111", sizeof(t.card_number)-1);
        j.append(t);
    }
    auto records = j.readAll();
    REQUIRE(records.size() == 5);
    CHECK(records[4].amount == doctest::Approx(500.0));
}
