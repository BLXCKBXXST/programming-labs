cmake_minimum_required(VERSION 3.20)
project(atm VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Основной исполняемый файл ────────────────────────────────────
set(ATM_SOURCES
    atm/main.cpp
    atm/card.cpp
    atm/account.cpp
    atm/transaction.cpp
    atm/journal.cpp
    atm/recovery.cpp
    atm/atm_engine.cpp
    atm/file_storage.cpp
)

add_executable(atm ${ATM_SOURCES})
target_include_directories(atm PRIVATE atm)

# ── Тесты (doctest) ──────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        v2.4.11
)
FetchContent_MakeAvailable(doctest)

set(TEST_COMMON_SOURCES
    atm/card.cpp
    atm/account.cpp
    atm/transaction.cpp
    atm/journal.cpp
    atm/recovery.cpp
    atm/file_storage.cpp
)

function(add_atm_test name file)
    add_executable(${name} ${file} ${TEST_COMMON_SOURCES})
    target_include_directories(${name} PRIVATE atm)
    target_link_libraries(${name} PRIVATE doctest::doctest)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

enable_testing()
add_atm_test(test_card    atm/tests/test_card.cpp)
add_atm_test(test_account atm/tests/test_account.cpp)
add_atm_test(test_journal atm/tests/test_journal.cpp)
