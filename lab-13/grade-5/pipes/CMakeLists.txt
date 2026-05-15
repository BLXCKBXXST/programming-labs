# создаём статическую библиотеку pipes из двух файлов
add_library(pipes STATIC read_pipe.c write_pipe.c)
# PUBLIC - чтобы любой кто подключится к pipes тоже видел pipes.h
target_include_directories(pipes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
