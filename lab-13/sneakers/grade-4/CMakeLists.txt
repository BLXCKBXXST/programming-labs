# CMakeLists.txt — файл конфигурации CMake
# CMake читает этот файл и сам генерирует Makefile под твою систему

# минимальная версия CMake, которая гарантированно понимает такой файл
cmake_minimum_required(VERSION 3.10)

# название проекта и язык
project(sneakers C)

# стандарт C99 (поддержка for (int i=0; ...) и др.)
set(CMAKE_C_STANDARD 99)

# выбор типа библиотеки через опцию -DLIB_TYPE=STATIC или -DLIB_TYPE=SHARED
# если не указано — по умолчанию STATIC
set(LIB_TYPE "STATIC" CACHE STRING "Library type: STATIC or SHARED")

# создаём библиотеку из sneakers.c
add_library(sneakers ${LIB_TYPE} src/sneakers.c)

# указываем где искать .h файлы для этой библиотеки (PUBLIC = и для тех, кто подключает)
target_include_directories(sneakers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# создаём исполняемый файл из main.c
add_executable(sneakers_app src/main.c)

# подключаем библиотеку к исполняемому файлу (PRIVATE = только для sneakers_app)
target_link_libraries(sneakers_app PRIVATE sneakers)
