cmake_minimum_required(VERSION 3.10)
project(sneakers_lab13 C)
set(CMAKE_C_STANDARD 99)

# выбор типа библиотеки через -DLIB_TYPE=STATIC или -DLIB_TYPE=SHARED
# по умолчанию: STATIC
set(LIB_TYPE "STATIC" CACHE STRING "Library type: STATIC or SHARED")

add_library(sneakers ${LIB_TYPE} src/sneakers.c)
target_include_directories(sneakers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(sneakers_app src/main.c)
target_link_libraries(sneakers_app PRIVATE sneakers)
