cmake_minimum_required(VERSION 3.10)
project(lab17_tinyexpr_tests C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

# Тестируемая библиотека — tinyexpr (third-party, скопирована в external/)
add_library(tinyexpr STATIC external/tinyexpr/tinyexpr.c)
target_include_directories(tinyexpr PUBLIC external/tinyexpr)
target_link_libraries(tinyexpr PUBLIC m)

# CMocka — установлен системно
find_library(CMOCKA_LIB cmocka REQUIRED)

enable_testing()

# grade-3 — без фреймворка, простые assert
add_executable(test_simple grade-3/test_simple.c)
target_link_libraries(test_simple PRIVATE tinyexpr)
add_test(NAME grade-3_simple COMMAND test_simple)

# grade-4 — CMocka, табличные тесты
add_executable(test_cmocka grade-4/test_cmocka.c)
target_link_libraries(test_cmocka PRIVATE tinyexpr ${CMOCKA_LIB})
add_test(NAME grade-4_cmocka COMMAND test_cmocka)

# grade-5 — расширенный набор, по одному ctest-кейсу на функцию
add_executable(test_full grade-5/test_full.c)
target_link_libraries(test_full PRIVATE tinyexpr ${CMOCKA_LIB})
add_test(NAME grade-5_full COMMAND test_full)
