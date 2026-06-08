#pragma once
#include <string>
#include "card.h"
#include "account.h"

// Работа с текстовыми файлами карт и счетов.
// Формат cards.txt:  <номер>:<pin_hash>:<blocked>
// Формат accounts.txt: <номер_карты>:<баланс>
class FileStorage {
public:
    explicit FileStorage(const std::string& data_dir);

    // Загрузить карту по номеру. Возвращает false если не найдена.
    bool loadCard(const std::string& number, Card& out) const;

    // Сохранить (обновить) карту
    void saveCard(const Card& card) const;

    // Загрузить счёт по номеру карты. Возвращает false если не найден.
    bool loadAccount(const std::string& card_number, Account& out) const;

    // Сохранить (обновить) счёт
    void saveAccount(const Account& account) const;

    // Создать демо-данные при первом запуске
    void createDemoDataIfNeeded() const;

private:
    std::string data_dir_;

    std::string cardsPath()    const { return data_dir_ + "/cards.txt"; }
    std::string accountsPath() const { return data_dir_ + "/accounts.txt"; }

    // Хэш PIN (повторяет логику из card.cpp, вынесен для инициализации)
    static std::string hashPin(const std::string& pin);
};
