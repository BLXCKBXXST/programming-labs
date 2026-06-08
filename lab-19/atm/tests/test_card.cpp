#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "card.h"

TEST_CASE("Card PIN check") {
    Card c("1111222233334444", "1234");
    CHECK(c.checkPin("1234") == true);
    CHECK(c.checkPin("0000") == false);
    CHECK(c.checkPin("")     == false);
}

TEST_CASE("Card block after 3 failures") {
    Card c("1111222233334444", "1234");
    CHECK(c.isBlocked() == false);
    c.addFailedAttempt();
    c.addFailedAttempt();
    int left = c.addFailedAttempt();
    CHECK(left == 0);
    CHECK(c.isBlocked() == true);
}

TEST_CASE("Card reset attempts") {
    Card c("1111222233334444", "1234");
    c.addFailedAttempt();
    c.addFailedAttempt();
    c.resetAttempts();
    CHECK(c.isBlocked() == false);
    CHECK(c.checkPin("1234") == true);
}
