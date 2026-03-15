# Создаём статическую библиотеку pipes из двух файлов
add_library(pipes STATIC read_pipe.c write_pipe.c)

# Указываем папку с заголовками как PUBLIC,
# чтобы другие цели, линкующиеся с pipes, тоже видели pipes.h
target_include_directories(pipes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
