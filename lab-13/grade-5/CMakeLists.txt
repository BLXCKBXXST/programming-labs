# минимальная версия cmake которая нужна для сборки проекта
cmake_minimum_required(VERSION 3.10)

# название проекта и язык программирования
project(cmake_task C)

# говорим cmake что пишем на c99
set(CMAKE_C_STANDARD 99)

# подключаем папку pipes - cmake сам зайдёт туда и выполнит её CMakeLists.txt
add_subdirectory(pipes)

# аналогично добавляем background, она внутри сама знает про pipes
add_subdirectory(background)

# создаём исполняемый файл из main.c
add_executable(cmake_task src/main.c)

# линкуем с background, pipes подцепится автоматически потому что мы объявили его PUBLIC в pipes/CMakeLists.txt
# PRIVATE значит что background нужен только внутри этой цели, наружу не уходит
target_link_libraries(cmake_task PRIVATE background)
