#include "recovery.h"
#include <iostream>

void Recovery::restore(Account& account,
                       const Journal& journal,
                       const std::string& card_number) {
    auto transactions = journal.readAll();
    int  applied = 0;
    for (const auto& t : transactions) {
        // Фильтруем только транзакции нужной карты
        if (std::string(t.card_number) != card_number) continue;
        account.applyTransaction(t);
        ++applied;
    }
    if (applied > 0) {
        std::cout << "[Recovery] Восстановлено транзакций: " << applied
                  << ", баланс: " << account.balance() << " руб\n";
    }
}

size_t Recovery::integrityCheck(const Journal& journal) {
    return journal.readAll().size();
}
