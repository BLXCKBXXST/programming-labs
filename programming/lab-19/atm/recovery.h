#pragma once
#include <string>
#include "account.h"
#include "journal.h"

// Восстанавливает состояние аккаунта из бинарного журнала.
// Вызывается при старте программы.
class Recovery {
public:
    // Читает все транзакции из журнала и применяет их к аккаунту.
    // initial_balance — начальный баланс до транзакций (из файла карты/счёта).
    static void restore(Account& account,
                        const Journal& journal,
                        const std::string& card_number);

    // Проверяет целостность журнала (количество полных записей)
    static size_t integrityCheck(const Journal& journal);
};
