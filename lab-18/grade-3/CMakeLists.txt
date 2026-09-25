cmake_minimum_required(VERSION 3.10)
project(paint)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(paint
    src/main.cpp
    src/paint_core.cpp
)

target_link_libraries(paint sfml-graphics sfml-window sfml-system)
