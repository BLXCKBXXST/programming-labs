#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../card.h"

TEST_CASE("Card PIN check") {
    Card c("1234567890123456",
        []() -> std::string {
            std::size_t h = std::hash<std::string>{}("1234" + std::string("atm_salt_2024"));
            std::ostringstream oss;
            oss << std::hex << std::setw(16) << std::setfill('0') << h;
            return oss.str();
        }()
    );
    CHECK(c.checkPin("1234") == true);
    CHECK(c.checkPin("0000") == false);
}

TEST_CASE("Card block after 3 failures") {
    Card c("1111222233334444", "dummyhash");
    CHECK(c.isBlocked() == false);
    c.addFailedAttempt(); // 1
    c.addFailedAttempt(); // 2
    int left = c.addFailedAttempt(); // 3 → blocked
    CHECK(left == 0);
    CHECK(c.isBlocked() == true);
}

TEST_CASE("Card reset attempts") {
    Card c("1111222233334444", "dummyhash");
    c.addFailedAttempt();
    c.addFailedAttempt();
    c.resetAttempts();
    CHECK(c.failedAttempts() == 0);
    CHECK(c.isBlocked() == false);
}
