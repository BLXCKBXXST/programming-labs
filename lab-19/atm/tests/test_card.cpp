#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "card.h"

// Card(number, pin_hash) expects an already-hashed PIN.
// makeCard(number, plain_pin) hashes it internally - use that in tests.

TEST_CASE("Card PIN check") {
    Card c = makeCard("1111222233334444", "1234");
    CHECK(c.checkPin("1234") == true);
    CHECK(c.checkPin("0000") == false);
    CHECK(c.checkPin("")     == false);
}

TEST_CASE("Card block after 3 failures") {
    Card c = makeCard("1111222233334444", "1234");
    CHECK(c.isBlocked() == false);
    c.addFailedAttempt();
    c.addFailedAttempt();
    int left = c.addFailedAttempt();
    CHECK(left == 0);
    CHECK(c.isBlocked() == true);
}

TEST_CASE("Card reset attempts") {
    Card c = makeCard("1111222233334444", "1234");
    c.addFailedAttempt();
    c.addFailedAttempt();
    c.resetAttempts();
    CHECK(c.isBlocked() == false);
    CHECK(c.checkPin("1234") == true);
}
