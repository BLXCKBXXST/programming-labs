#include "atm_engine.h"
#include "tui.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstring>
#include <algorithm>

using namespace tui;

// ─────────────────────────────────────────────────────────────────────────────
AtmEngine::AtmEngine(const std::string& data_dir)
    : storage_(data_dir),
      journal_path_(data_dir + "/journal.bin")
{
    storage_.createDemoDataIfNeeded();
    journal_ = std::make_unique<Journal>(journal_path_);
}

// ─────────────────────────────────────────────────────────────────────────────
// Вспомогательные
// ─────────────────────────────────────────────────────────────────────────────
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
    std::strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M", std::localtime(&t));
    return buf;
}

// ─────────────────────────────────────────────────────────────────────────────
// Шапка банкомата
// ─────────────────────────────────────────────────────────────────────────────
static void drawHeader(const std::string& subtitle = "") {
    tui::clearScreen();
    boxTop();
    boxRow(std::string(BOLD) + CYAN + center("  ╔═╗╔╦╗╔╦╗  ", W) + RESET);
    boxRow(std::string(BOLD) + YELLOW + center("  БАНКОМАТ  ATM v1.0  ", W) + RESET);
    boxRow(std::string(DIM)  + WHITE  + center("ул. Советская, 1 · Новосибирск", W) + RESET);
    if (!subtitle.empty()) {
        boxSep();
        boxRow(std::string(BOLD) + WHITE + center(subtitle, W) + RESET);
    }
    boxSep();
}

// ─────────────────────────────────────────────────────────────────────────────
void AtmEngine::run() {
    while (true) {
        drawHeader();
        boxRow(center("Введите номер карты", W));
        boxEmpty();
        boxRow(std::string(DIM) + center("demo: 1234567890123456  PIN: 1234", W) + RESET);
        boxRow(std::string(DIM) + center("      9876543210987654  PIN: 5678", W) + RESET);
        boxEmpty();
        boxRow(std::string(DIM) + center("'exit' — выход", W) + RESET);
        boxBot();
        showCursor();

        std::cout << "  " << CYAN << "Карта: " << RESET;
        std::string card_number;
        std::cin >> card_number;
        if (card_number == "exit" || card_number == "q") {
            drawHeader("Спасибо за использование!");
            boxEmpty();
            boxRow(center("До свидания! 👋", W));
            boxEmpty();
            boxBot();
            showCursor();
            return;
        }

        Card card;
        if (!storage_.loadCard(card_number, card)) {
            showMsg("Карта не найдена: " + card_number, false);
            continue;
        }
        if (card.isBlocked()) {
            showMsg("Карта ЗАБЛОКИРОВАНА\n" + center("Обратитесь в отделение банка", W), false);
            continue;
        }

        Account account;
        if (!storage_.loadAccount(card_number, account)) {
            showMsg("Счёт не найден для карты " + card_number, false);
            continue;
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

// ─────────────────────────────────────────────────────────────────────────────
// PIN-экран
// ─────────────────────────────────────────────────────────────────────────────
bool AtmEngine::screenPin(Card& card) {
    for (int attempt = 1; attempt <= 3 && !card.isBlocked(); ++attempt) {
        drawHeader("Введите PIN-код");
        boxEmpty();
        boxRow(std::string("  ") + CYAN + maskedCard(card.number()) + RESET);
        boxEmpty();

        // Индикатор попыток
        std::string dots;
        for (int i = 0; i < 3; ++i)
            dots += (i < attempt - 1)
                ? std::string(RED)    + "✗ " + RESET
                : std::string(YELLOW) + "○ " + RESET;
        boxRow("  Попытка: " + dots);
        boxEmpty();
        boxBot();

        std::string pin = readPin("  " + std::string(YELLOW) + "PIN " + RESET + "→ ");

        if (card.checkPin(pin)) {
            card.resetAttempts();
            return true;
        }
        int left = card.addFailedAttempt();
        if (left == 0) return false;
        showMsg("Неверный PIN. Осталось попыток: " + std::to_string(left), false);
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// Главное меню
// ─────────────────────────────────────────────────────────────────────────────
void AtmEngine::screenMenu(Card& card, Account& account) {
    while (true) {
        drawHeader("Главное меню");
        boxRow(std::string("  ") + DIM + "Карта: " + RESET + CYAN + maskedCard(card.number()) + RESET);
        boxRow(std::string("  ") + DIM + "Баланс: " + RESET
               + BOLD + GREEN + fmtMoney(account.balance()) + RESET);
        boxSep();
        boxEmpty();

        // arrowMenu рисует строки начиная с текущей позиции
        int choice = arrowMenu({
            "  💰  Баланс",
            "  📤  Снять наличные",
            "  📥  Пополнить",
            "  📋  История (последние 5)",
            "  🚪  Завершить сессию"
        });

        boxBot();

        switch (choice) {
            case 0: screenBalance(account);         break;
            case 1: screenWithdraw(card, account);  break;
            case 2: screenDeposit(card, account);   break;
            case 3: screenHistory(account);         break;
            case 4: return;
            case -1: return;  // ESC
            default: break;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Баланс
// ─────────────────────────────────────────────────────────────────────────────
void AtmEngine::screenBalance(const Account& account) {
    drawHeader("Баланс счёта");
    boxEmpty();
    boxRow(std::string("  ") + WHITE + "Текущий баланс:" + RESET);
    boxRow(std::string("  ") + BOLD + GREEN + "  " + fmtMoney(account.balance()) + RESET);
    boxEmpty();

    char tbuf[32];
    std::time_t now = std::time(nullptr);
    std::strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H:%M:%S", std::localtime(&now));
    boxRow(std::string("  ") + DIM + "На: " + tbuf + RESET);
    boxEmpty();

    // Запись в журнал
    Transaction t{};
    t.type = TransactionType::CHECK;
    t.amount = 0.0; t.fee = 0.0;
    t.balance_after = account.balance();
    t.timestamp = now;
    std::strncpy(t.card_number, account.cardNumber().c_str(), sizeof(t.card_number)-1);
    journal_->append(t);

    pause();
}

// ─────────────────────────────────────────────────────────────────────────────
// Снятие
// ─────────────────────────────────────────────────────────────────────────────
void AtmEngine::screenWithdraw(Card& /*card*/, Account& account) {
    drawHeader("Снятие наличных");
    boxRow(std::string("  ") + DIM + "Лимит за раз: 10 000 руб   Суточный: 50 000 руб" + RESET);
    boxRow(std::string("  ") + DIM + "Комиссия: 1% (мин. 30 руб)" + RESET);
    boxEmpty();
    boxRow(std::string("  ") + "Баланс: " + BOLD + GREEN + fmtMoney(account.balance()) + RESET);
    boxEmpty();
    boxBot();
    showCursor();
    std::cout << "  " << CYAN << "Сумма руб → " << RESET;

    double amount = 0;
    if (!(std::cin >> amount)) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showMsg("Неверный ввод.", false); return;
    }

    double fee = std::max(amount * 0.01, 30.0);
    double total = amount + fee;

    // Подтверждение
    drawHeader("Подтверждение");
    boxEmpty();
    boxRow(std::string("  ") + WHITE + "Сумма к выдаче:  " + BOLD + fmtMoney(amount) + RESET);
    boxRow(std::string("  ") + WHITE + "Комиссия:        " + YELLOW + fmtMoney(fee) + RESET);
    boxRow(std::string("  ") + WHITE + "Итого списание:  " + RED + BOLD + fmtMoney(total) + RESET);
    boxEmpty();

    int ok = arrowMenu({"  ✅  Подтвердить", "  ❌  Отмена"});
    boxBot();
    if (ok != 0) { showMsg("Операция отменена.", false); return; }

    try {
        double nb = account.withdraw(amount);
        auto txs = account.lastTransactions(1);
        if (!txs.empty()) journal_->append(txs.back());
        storage_.saveAccount(account);
        showMsg("Выдано: " + fmtMoney(amount) + "\n  Новый баланс: " + fmtMoney(nb), true);
    } catch (const std::exception& e) {
        showMsg(std::string(e.what()), false);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Пополнение
// ─────────────────────────────────────────────────────────────────────────────
void AtmEngine::screenDeposit(Card& /*card*/, Account& account) {
    drawHeader("Пополнение счёта");
    boxRow(std::string("  ") + "Баланс: " + BOLD + GREEN + fmtMoney(account.balance()) + RESET);
    boxEmpty();
    boxBot();
    showCursor();
    std::cout << "  " << CYAN << "Сумма руб → " << RESET;

    double amount = 0;
    if (!(std::cin >> amount)) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showMsg("Неверный ввод.", false); return;
    }

    try {
        double nb = account.deposit(amount);
        auto txs = account.lastTransactions(1);
        if (!txs.empty()) journal_->append(txs.back());
        storage_.saveAccount(account);
        showMsg("Зачислено: " + fmtMoney(amount) + "\n  Баланс: " + fmtMoney(nb), true);
    } catch (const std::exception& e) {
        showMsg(std::string(e.what()), false);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// История
// ─────────────────────────────────────────────────────────────────────────────
void AtmEngine::screenHistory(const Account& account) {
    drawHeader("История операций");
    auto txs = account.lastTransactions(5);
    if (txs.empty()) {
        boxEmpty();
        boxRow(center("Нет операций", W));
        boxEmpty();
    } else {
        // шапка таблицы
        boxRow(std::string(DIM) +
               ljust("Дата", 16) + ljust("Тип", 11) +
               ljust("Сумма", 10) + "Баланс" + RESET);
        boxSep();
        for (int i = (int)txs.size()-1; i >= 0; --i) {
            const auto& t = txs[i];
            std::string type_str, col;
            switch (t.type) {
                case TransactionType::DEPOSIT:  type_str = "ЗАЧИСЛ"; col = GREEN;  break;
                case TransactionType::WITHDRAW: type_str = "ВЫДАЧА"; col = RED;    break;
                case TransactionType::CHECK:    type_str = "БАЛАНС"; col = YELLOW; break;
            }
            std::ostringstream row;
            row << std::string(col) << ljust(fmtTime(t.timestamp), 16) << RESET
                << std::string(BOLD) << std::string(col) << ljust(type_str, 8) << RESET << "  "
                << std::fixed << std::setprecision(0)
                << ljust(std::to_string((int)t.amount), 10)
                << std::to_string((int)t.balance_after);
            boxRow(row.str());
        }
    }
    pause();
}

// ─────────────────────────────────────────────────────────────────────────────
void AtmEngine::showMsg(const std::string& msg, bool ok) {
    drawHeader(ok ? "Успешно" : "Ошибка");
    boxEmpty();
    std::istringstream ss(msg);
    std::string line;
    while (std::getline(ss, line, '\n')) {
        if (ok)
            boxRow(std::string("  ") + GREEN + BOLD + line + RESET);
        else
            boxRow(std::string("  ") + RED   + BOLD + line + RESET);
    }
    boxEmpty();
    pause();
}
