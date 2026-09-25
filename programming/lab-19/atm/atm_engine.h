#pragma once
#include <memory>
#include <string>
#include "card.h"
#include "account.h"
#include "journal.h"
#include "file_storage.h"
#include "recovery.h"

class AtmEngine {
public:
    explicit AtmEngine(const std::string& data_dir);
    void run();

private:
    bool screenPin(Card& card);
    void screenMenu(Card& card, Account& account);
    void screenBalance(const Account& account);
    void screenWithdraw(Card& card, Account& account);
    void screenDeposit(Card& card, Account& account);
    void screenHistory(const Account& account);
    void showMsg(const std::string& msg, bool ok);

    FileStorage              storage_;
    std::unique_ptr<Journal> journal_;
    std::string              journal_path_;
};
