cmake_minimum_required(VERSION 3.10)
project(roguelike_lab13 C)
set(CMAKE_C_STANDARD 99)

# выбор типа библиотеки через -DLIB_TYPE=STATIC или -DLIB_TYPE=SHARED
# по умолчанию: STATIC
set(LIB_TYPE "STATIC" CACHE STRING "Library type: STATIC or SHARED")

add_library(room ${LIB_TYPE} src/room.c)
target_include_directories(room PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(rooms src/main.c)
target_link_libraries(rooms PRIVATE room)
