cmake_minimum_required(VERSION 3.10)
project(SneakersProject C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra)

set(LIB_TYPE "STATIC" CACHE STRING "Тип библиотеки: STATIC или SHARED")
set_property(CACHE LIB_TYPE PROPERTY STRINGS STATIC SHARED)

message(STATUS "Building library as: ${LIB_TYPE}")

add_library(sorting ${LIB_TYPE} src/sneakers.c)
target_include_directories(sorting PUBLIC include)

add_executable(sneakers src/main.c)
target_link_libraries(sneakers PRIVATE sorting)