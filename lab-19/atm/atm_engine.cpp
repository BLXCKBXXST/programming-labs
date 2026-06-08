#include "atm_engine.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>

AtmEngine::AtmEngine(const std::string& data_dir)
    : storage_(data_dir),
      journal_path_(data_dir + "/journal.bin")
{
    storage_.createDemoDataIfNeeded();
    journal_ = std::make_unique<Journal>(journal_path_);
}

void AtmEngine::run() {
    while (true) {
        screenWelcome();
        std::string card_number;
        std::cout << "Введите номер карты (или 'exit' для выхода): ";
        std::cin >> card_number;
        if (card_number == "exit") {
            std::cout << "\nДо свидания!\n";
            break;
        }

        Card card;
        if (!storage_.loadCard(card_number, card)) {
            printError("Карта не найдена: " + card_number);
            continue;
        }
        if (card.isBlocked()) {
            printError("Карта заблокирована. Обратитесь в банк.");
            continue;
        }

        Account account;
        if (!storage_.loadAccount(card_number, account)) {
            printError("Счёт не найден для карты " + card_number);
            continue;
        }

        // Recovery: восстанавливаем баланс из журнала
        Recovery::restore(account, *journal_, card_number);

        screenPin(card);
        if (card.isBlocked()) {
            storage_.saveCard(card);
            printError("Карта заблокирована после 3 неверных попыток.");
            continue;
        }

        screenMenu(card, account);
        storage_.saveAccount(account);
    }
}

void AtmEngine::screenWelcome() {
    printSeparator();
    std::cout << "         БАНКОМАТ v1.0\n";
    printSeparator();
}

void AtmEngine::screenPin(Card& card) {
    for (int attempt = 0; attempt < 3 && !card.isBlocked(); ++attempt) {
        std::string pin;
        std::cout << "Введите PIN (попытка " << attempt+1 << "/3): ";
        std::cin >> pin;
        if (card.checkPin(pin)) {
            card.resetAttempts();
            std::cout << "PIN принят.\n";
            return;
        } else {
            int left = card.addFailedAttempt();
            if (left == 0)
                std::cout << "Неверный PIN. Карта ЗАБЛОКИРОВАНА.\n";
            else
                std::cout << "Неверный PIN. Осталось попыток: " << left << "\n";
        }
    }
}

void AtmEngine::screenMenu(Card& card, Account& account) {
    bool active = true;
    while (active) {
        printSeparator();
        std::cout << "Карта: **** **** **** "
                  << card.number().substr(card.number().size() > 4 ?
                        card.number().size()-4 : 0)
                  << "\n";
        std::cout << "1. Баланс\n"
                     "2. Снять наличные\n"
                     "3. Пополнить\n"
                     "4. История (последние 5)\n"
                     "0. Выйти из сессии\n";
        printSeparator();
        std::cout << "Выбор: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: screenBalance(account);         break;
            case 2: screenWithdraw(card, account);  break;
            case 3: screenDeposit(card, account);   break;
            case 4: screenHistory(account);         break;
            case 0: active = false;                 break;
            default: printError("Неверный пункт меню."); break;
        }
    }
}

void AtmEngine::screenBalance(const Account& account) {
    printSeparator();
    std::cout << std::fixed << std::setprecision(2)
              << "Баланс: " << account.balance() << " руб\n";

    Transaction t{};
    t.type          = TransactionType::CHECK;
    t.amount        = 0.0;
    t.fee           = 0.0;
    t.balance_after = account.balance();
    t.timestamp     = std::time(nullptr);
    std::strncpy(t.card_number, account.cardNumber().c_str(),
                 sizeof(t.card_number)-1);
    journal_->append(t);
}

void AtmEngine::screenWithdraw(Card& /*card*/, Account& account) {
    printSeparator();
    std::cout << "Введите сумму для снятия (руб): ";
    double amount;
    if (!(std::cin >> amount)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printError("Неверный ввод.");
        return;
    }
    try {
        double fee = std::max(amount * 0.01, 30.0);
        std::cout << std::fixed << std::setprecision(2)
                  << "Комиссия: " << fee << " руб  "
                  << "Итого спишется: " << amount + fee << " руб\n";
        std::cout << "Подтвердить? (y/n): ";
        char c; std::cin >> c;
        if (c != 'y' && c != 'Y') { std::cout << "Отменено.\n"; return; }

        double new_bal = account.withdraw(amount);
        // Пишем в журнал последнюю транзакцию
        auto txs = account.lastTransactions(1);
        if (!txs.empty()) journal_->append(txs.back());

        storage_.saveAccount(account);
        printSuccess("Выдано: " + [&]{
            std::ostringstream s;
            s << std::fixed << std::setprecision(2) << amount;
            return s.str();
        }() + " руб. Новый баланс: " + [&]{
            std::ostringstream s;
            s << std::fixed << std::setprecision(2) << new_bal;
            return s.str();
        }() + " руб");
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void AtmEngine::screenDeposit(Card& /*card*/, Account& account) {
    printSeparator();
    std::cout << "Введите сумму для пополнения (руб): ";
    double amount;
    if (!(std::cin >> amount)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printError("Неверный ввод.");
        return;
    }
    try {
        double new_bal = account.deposit(amount);
        auto txs = account.lastTransactions(1);
        if (!txs.empty()) journal_->append(txs.back());
        storage_.saveAccount(account);
        printSuccess("Счёт пополнен на " + [&]{
            std::ostringstream s;
            s << std::fixed << std::setprecision(2) << amount;
            return s.str();
        }() + " руб. Баланс: " + [&]{
            std::ostringstream s;
            s << std::fixed << std::setprecision(2) << new_bal;
            return s.str();
        }() + " руб");
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void AtmEngine::screenHistory(const Account& account) {
    printSeparator();
    std::cout << "  История последних 5 операций\n";
    printSeparator();
    auto txs = account.lastTransactions(5);
    if (txs.empty()) {
        std::cout << "Нет операций.\n";
        return;
    }
    for (int i = (int)txs.size()-1; i >= 0; --i) {
        const auto& t = txs[i];
        char tbuf[32];
        std::strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&t.timestamp));
        std::string type_str;
        switch (t.type) {
            case TransactionType::DEPOSIT:  type_str = "ПОПОЛНЕНИЕ"; break;
            case TransactionType::WITHDRAW: type_str = "СНЯТИЕ    "; break;
            case TransactionType::CHECK:    type_str = "БАЛАНС    "; break;
        }
        std::cout << tbuf << "  " << type_str
                  << std::fixed << std::setprecision(2)
                  << "  сумма: " << t.amount
                  << "  комиссия: " << t.fee
                  << "  баланс: " << t.balance_after << " руб\n";
    }
}

void AtmEngine::printSeparator() {
    std::cout << "--------------------------------------\n";
}
void AtmEngine::printError(const std::string& msg) {
    std::cout << "[!] " << msg << "\n";
}
void AtmEngine::printSuccess(const std::string& msg) {
    std::cout << "[OK] " << msg << "\n";
}
