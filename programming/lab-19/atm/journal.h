#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "transaction.h"

// Append-only бинарный журнал транзакций.
// Формат: последовательные записи sizeof(Transaction),
// без перезаписи — только дозапись (append).
class Journal {
public:
    explicit Journal(const std::string& path);
    ~Journal();

    // Записать транзакцию в конец файла
    void append(const Transaction& t);

    // Прочитать все транзакции (для recovery)
    std::vector<Transaction> readAll() const;

    // Путь к файлу
    const std::string& path() const { return path_; }

private:
    std::string   path_;
    std::ofstream out_;

    void openAppend();
};
