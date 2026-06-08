#pragma once
#include <memory>
#include <string>
#include "card.h"
#include "account.h"
#include "journal.h"
#include "file_storage.h"
#include "recovery.h"

// Основной движок банкомата.
// Управляет сессией, лимитами и потоком команд.
class AtmEngine {
public:
    explicit AtmEngine(const std::string& data_dir);

    // Запустить главный цикл банкомата
    void run();

private:
    // --- Экраны ---
    void screenWelcome();
    void screenPin(Card& card);
    void screenMenu(Card& card, Account& account);
    void screenBalance(const Account& account);
    void screenWithdraw(Card& card, Account& account);
    void screenDeposit(Card& card, Account& account);
    void screenHistory(const Account& account);

    // --- Вспомогательное ---
    void printSeparator();
    void printError(const std::string& msg);
    void printSuccess(const std::string& msg);

    // --- Данные ---
    FileStorage                storage_;
    std::unique_ptr<Journal>   journal_;
    std::string                journal_path_;
};
