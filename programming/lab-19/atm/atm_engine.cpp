#include "atm_engine.h"
#include "tui.h"
#include <algorithm>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace tui;

AtmEngine::AtmEngine(const std::string& data_dir)
    : storage_(data_dir), journal_path_(data_dir + "/journal.bin")
{
    storage_.createDemoDataIfNeeded();
    journal_ = std::make_unique<Journal>(journal_path_);
}

static std::string fmtMoney(double v) {
    std::ostringstream s;
    s << std::fixed << std::setprecision(2) << v << " руб";
    return s.str();
}
static std::string maskedCard(const std::string& num) {
    if (num.size() < 4) return num;
    return "**** **** **** " + num.substr(num.size() - 4);
}
static std::string fmtTime(std::time_t t) {
    char buf[32];
    std::strftime(buf, sizeof(buf), "%d.%m %H:%M", std::localtime(&t));
    return buf;
}

static void drawHeader(const std::string& subtitle = "") {
    clearScreen();
    boxTop();
    boxRow(std::string(BOLD) + CYAN + center("  BANK ATM v1.0  ", W) + RESET);
    boxRow(std::string(DIM) + WHITE + center("ул. Советская, 1  Новосибирск", W) + RESET);
    if (!subtitle.empty()) {
        boxSep();
        boxRow(std::string(BOLD) + WHITE + center(subtitle, W) + RESET);
    }
    boxSep();
}

void AtmEngine::run() {
    while (true) {
        drawHeader();
        boxRow(center("Введите номер карты", W));
        boxEmpty();
        boxRow(std::string(DIM) + center("demo: 1234567890123456  PIN: 1234", W) + RESET);
        boxRow(std::string(DIM) + center("      9876543210987654  PIN: 5678", W) + RESET);
        boxEmpty();
        boxRow(std::string(DIM) + center("exit - выход", W) + RESET);
        boxBot();
        showCursor();

        std::cout << "  " << CYAN << "Карта: " << RESET;
        std::string card_number;
        std::cin >> card_number;

        if (card_number == "exit" || card_number == "q") {
            drawHeader("Спасибо за использование!");
            boxRow(center("До свидания!", W));
            boxBot();
            return;
        }

        Card card;
        if (!storage_.loadCard(card_number, card)) {
            showMsg("Карта не найдена: " + card_number, false); continue;
        }
        if (card.isBlocked()) {
            showMsg("Карта ЗАБЛОКИРОВАНА\nОбратитесь в отделение банка", false); continue;
        }

        Account account;
        if (!storage_.loadAccount(card_number, account)) {
            showMsg("Счёт не найден для карты " + card_number, false); continue;
        }

        Recovery::restore(account, *journal_, card_number);

        if (!screenPin(card)) {
            storage_.saveCard(card);
            if (card.isBlocked())
                showMsg("Карта ЗАБЛОКИРОВАНА\nПревышено число попыток PIN", false);
            continue;
        }

        screenMenu(card, account);
        storage_.saveAccount(account);
    }
}

bool AtmEngine::screenPin(Card& card) {
    for (int attempt = 1; attempt <= 3 && !card.isBlocked(); ++attempt) {
        drawHeader("Введите PIN-код");
        boxRow(std::string("  Карта: ") + CYAN + maskedCard(card.number()) + RESET);
        boxEmpty();
        std::ostringstream att;
        att << "  Попытка " << attempt << " из 3";
        boxRow(att.str());
        boxBot();

        std::string pin = readPin(std::string("  ") + YELLOW + "PIN -> " + RESET);
        if (card.checkPin(pin)) { card.resetAttempts(); return true; }
        int left = card.addFailedAttempt();
        if (left == 0) return false;
        showMsg("Неверный PIN. Осталось попыток: " + std::to_string(left), false);
    }
    return false;
}

void AtmEngine::screenMenu(Card& card, Account& account) {
    while (true) {
        drawHeader("Главное меню");
        boxRow(std::string("  Карта:  ") + CYAN + maskedCard(card.number()) + RESET);
        boxRow(std::string("  Баланс: ") + GREEN + BOLD + fmtMoney(account.balance()) + RESET);
        boxSep();
        int choice = simpleMenu({
            "Баланс",
            "Снять наличные",
            "Пополнить",
            "История (последние 5)",
            "Завершить сессию"
        });
        switch (choice) {
            case 0: screenBalance(account);        break;
            case 1: screenWithdraw(card, account); break;
            case 2: screenDeposit(card, account);  break;
            case 3: screenHistory(account);        break;
            case 4: return;
            default: break;
        }
    }
}

void AtmEngine::screenBalance(const Account& account) {
    drawHeader("Баланс счёта");
    boxEmpty();
    boxRow("  Текущий баланс:");
    boxRow(std::string("    ") + GREEN + BOLD + fmtMoney(account.balance()) + RESET);
    boxEmpty();
    char tbuf[32];
    std::time_t now = std::time(nullptr);
    std::strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H:%M:%S", std::localtime(&now));
    boxRow(std::string("  ") + DIM + "На: " + tbuf + RESET);
    boxEmpty();

    Transaction t{};
    t.type = TransactionType::CHECK;
    t.amount = 0.0; t.fee = 0.0;
    t.balance_after = account.balance();
    t.timestamp = now;
    std::strncpy(t.card_number, account.cardNumber().c_str(), sizeof(t.card_number) - 1);
    journal_->append(t);

    boxBot();
    tui::waitKey();
}

void AtmEngine::screenWithdraw(Card& /*card*/, Account& account) {
    drawHeader("Снятие наличных");
    boxRow(std::string(DIM) + "  Лимит за раз: 10 000 руб" + RESET);
    boxRow(std::string(DIM) + "  Суточный лимит: 50 000 руб" + RESET);
    boxRow(std::string(DIM) + "  Комиссия: 1% (мин. 30 руб)" + RESET);
    boxEmpty();
    boxRow(std::string("  Баланс: ") + GREEN + BOLD + fmtMoney(account.balance()) + RESET);
    boxBot();
    showCursor();

    std::cout << "  " << CYAN << "Сумма руб -> " << RESET;
    double amount = 0.0;
    if (!(std::cin >> amount)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        showMsg("Неверный ввод", false); return;
    }
    std::cin.ignore(10000, '\n');

    double fee   = std::max(amount * 0.01, 30.0);
    double total = amount + fee;

    drawHeader("Подтверждение снятия");
    boxRow(std::string("  К выдаче:  ") + fmtMoney(amount));
    boxRow(std::string("  Комиссия:  ") + YELLOW + fmtMoney(fee) + RESET);
    boxRow(std::string("  Спишется:  ") + RED + BOLD + fmtMoney(total) + RESET);
    boxSep();
    int ok = simpleMenu({"Подтвердить", "Отмена"});
    if (ok != 0) { showMsg("Операция отменена", false); return; }

    try {
        double new_bal = account.withdraw(amount);
        auto txs = account.lastTransactions(1);
        if (!txs.empty()) journal_->append(txs.back());
        storage_.saveAccount(account);
        showMsg("Выдано: " + fmtMoney(amount) + "\nНовый баланс: " + fmtMoney(new_bal), true);
    } catch (const std::exception& e) {
        showMsg(e.what(), false);
    }
}

void AtmEngine::screenDeposit(Card& /*card*/, Account& account) {
    drawHeader("Пополнение счёта");
    boxRow(std::string("  Баланс: ") + GREEN + BOLD + fmtMoney(account.balance()) + RESET);
    boxBot();
    showCursor();

    std::cout << "  " << CYAN << "Сумма руб -> " << RESET;
    double amount = 0.0;
    if (!(std::cin >> amount)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        showMsg("Неверный ввод", false); return;
    }
    std::cin.ignore(10000, '\n');

    try {
        double new_bal = account.deposit(amount);
        auto txs = account.lastTransactions(1);
        if (!txs.empty()) journal_->append(txs.back());
        storage_.saveAccount(account);
        showMsg("Зачислено: " + fmtMoney(amount) + "\nБаланс: " + fmtMoney(new_bal), true);
    } catch (const std::exception& e) {
        showMsg(e.what(), false);
    }
}

void AtmEngine::screenHistory(const Account& account) {
    drawHeader("История операций");
    auto txs = account.lastTransactions(5);
    if (txs.empty()) {
        boxRow(center("Нет операций", W));
    } else {
        boxRow(std::string(DIM) +
               ljust("Дата", 12) + ljust("Тип", 8) +
               ljust("Сумма", 10) + "Баланс" + RESET);
        boxSep();
        for (int i = (int)txs.size() - 1; i >= 0; --i) {
            const auto& t = txs[i];
            std::string tp;
            switch (t.type) {
                case TransactionType::DEPOSIT:  tp = "ПОПОЛН"; break;
                case TransactionType::WITHDRAW: tp = "СНЯТИЕ"; break;
                case TransactionType::CHECK:    tp = "БАЛАНС"; break;
            }
            std::ostringstream row;
            row << ljust(fmtTime(t.timestamp), 12)
                << ljust(tp, 8)
                << ljust(std::to_string((int)t.amount), 10)
                << (int)t.balance_after;
            boxRow(row.str());
        }
    }
    boxBot();
    tui::waitKey();
}

void AtmEngine::showMsg(const std::string& msg, bool ok) {
    drawHeader(ok ? "Успешно" : "Ошибка");
    std::istringstream ss(msg);
    std::string line;
    while (std::getline(ss, line))
        boxRow(std::string("  ") + (ok ? GREEN : RED) + BOLD + line + RESET);
    boxEmpty();
    boxBot();
    tui::waitKey();
}
