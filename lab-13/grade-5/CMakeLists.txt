cmake_minimum_required(VERSION 3.10)
project(SneakersProject C)

# Стандарт C
set(CMAKE_C_STANDARD 99)

# Флаги компиляции
add_compile_options(-Wall -Wextra)

# -DCMAKE_BUILD_TYPE=Debug   -> включает отладочные символы (-g), отключает оптимизацию
# -DCMAKE_BUILD_TYPE=Release -> включает оптимизацию (-O3), убирает отладку
# Использование: cmake -DCMAKE_BUILD_TYPE=Release ..

# Выбор типа библиотеки через -DLIB_TYPE=STATIC или -DLIB_TYPE=SHARED
# Пример: cmake -DLIB_TYPE=SHARED ..
set(LIB_TYPE "STATIC" CACHE STRING "Тип библиотеки: STATIC или SHARED")
set_property(CACHE LIB_TYPE PROPERTY STRINGS STATIC SHARED)

message(STATUS "Building library as: ${LIB_TYPE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Собираем библиотеку из sneakers.c
add_library(sorting ${LIB_TYPE} src/sneakers.c)

# Указываем папку с заголовками для библиотеки
target_include_directories(sorting PUBLIC include)

# Собираем исполняемый файл
add_executable(sneakers src/main.c)

# Линкуем исполняемый файл с библиотекой
target_link_libraries(sneakers PRIVATE sorting)
