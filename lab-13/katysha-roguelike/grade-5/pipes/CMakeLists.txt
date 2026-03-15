# создаём статическую библиотеку pipes
add_library(pipes STATIC read_pipe.c write_pipe.c)
# PUBLIC - чтобы pipes.h был виден всем кто линкуется с pipes
target_include_directories(pipes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
