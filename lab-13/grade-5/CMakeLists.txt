cmake_minimum_required(VERSION 3.10)
project(cmake_task C)

set(CMAKE_C_STANDARD 99)

# Добавляем подпапку pipes — CMake зайдёт в неё и выполнит её CMakeLists.txt
add_subdirectory(pipes)

# Добавляем подпапку background — внутри она сама подцепится к pipes
add_subdirectory(background)

# Создаём исполняемый файл из src/main.c
add_executable(cmake_task src/main.c)

# Линкуем исполняемый файл с библиотекой background
# (background сама потянет pipes автоматически)
target_link_libraries(cmake_task PRIVATE background)
